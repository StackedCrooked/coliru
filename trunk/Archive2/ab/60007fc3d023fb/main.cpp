#include <iostream>
#include <utility>
#include <memory>

template<class...Ts>
using void_t = std::conditional_t<true,void,std::tuple<Ts...>>;

template<class Sig,class=void>
struct is_invokable:std::false_type {};
template<class F, class... Ts>
struct is_invokable<
    F(Ts...),
    void_t<decltype(std::declval<F>()(std::declval<Ts>()...))>
>:std::true_type {};

// Curry helper is sort of a manual lambda.  It captures a function and one argument
// It isn't written as a lambda so we can enable proper rvalue forwarding when it is
// used in an rvalue context, which is important when currying:
template<class F, class T>
struct curry_helper {
    F f;
    T t;

    template<class...Args>
    auto operator()(Args&&...args)const& ->
      decltype(f(t, std::forward<Args>(args)...)) {
        return f(t, std::forward<Args>(args)...);
    }
    template<class...Args>
    auto operator()(Args&&...args)& ->
      decltype(f(t, std::forward<Args>(args)...)) {
        return f(t, std::forward<Args>(args)...);
    }
    template<class...Args>
    auto operator()(Args&&...args)&& ->
      decltype(std::move(f)(std::move(t), std::forward<Args>(args)...)) {
        return std::move(f)(std::move(t), std::forward<Args>(args)...);
    }
};

template <typename F, typename...Args>
static auto apply_(std::true_type, F&& f, Args&&...args) ->
  decltype(std::forward<F>(f)(std::forward<Args>(args)...)) {
    return std::forward<F>(f)(std::forward<Args>(args)...);
}

template <typename F, typename Arg>
static auto apply_(std::false_type, F&& f, Arg&& arg) ->
  curry_t<curry_helper<F, std::decay_t<Arg>>> {
    return {{std::forward<F>(f), std::forward<Arg>(arg)}};
}

template <typename F, typename First, typename...Args>
static auto apply_(std::false_type, F&& f, First&& first, Args&&...args) {
    return curry_t<curry_helper<F, std::decay_t<First>>>{
        {std::forward<F>(f), std::forward<First>(first)}
    }(std::forward<Args>(args)...);
}

template <typename F, typename...Args>
static auto apply(F&& f, Args&&...args) ->
  decltype(apply_(is_invokable<F(Args...)>{}, std::forward<F>(f), std::forward<Args>(args)...)) {
    return apply_(is_invokable<F(Args...)>{}, std::forward<F>(f), std::forward<Args>(args)...);
}

template<class F>
class curry_t {
public:
    F f;

    template<class...Args>
	auto operator()(Args&&...args)const& ->
      decltype(apply(f, std::forward<Args>(args)...)) {
		return apply(f, std::forward<Args>(args)...);
	}
    template<class...Args>
	auto operator()(Args&&...args)& ->
      decltype(apply(f, std::forward<Args>(args)...)) {
		return apply(f, std::forward<Args>(args)...);
	}
    template<class...Args>
	auto operator()(Args&&...args)&& ->
      decltype(apply(std::move(f), std::forward<Args>(args)...)) {
		return apply(std::move(f), std::forward<Args>(args)...);
	}
};

template<class F>
curry_t<std::decay_t<F>> curry( F&& f ) { return {std::forward<F>(f)}; }

static struct foo_t {
    double operator()(double x, int y, std::nullptr_t, std::nullptr_t)const{std::cout << "first\n"; return x*y;}
    char operator()(char c, int x)const{std::cout << "second\n"; return c+x;}
    void operator()(char const*s)const{std::cout << "hello " << s << "\n";}
} foo;

int main() {
	auto f = curry(foo);
    // Call the 3rd overload:
    f("world");
    // testing the ability to "jump over" the second overload:
    std::cout << f(3.14,10,nullptr)(nullptr) << "\n";
    // call the 2nd overload:
    auto x = f('a',2);
    std::cout << x << "\n";
    // again:
    x =  f('a')(2);
    std::cout << x << "\n";
    std::cout << is_invokable<decltype(foo)(double, int)>{} << "\n";
    std::cout << is_invokable<decltype(foo)(double)>{} << "\n";
    std::cout << is_invokable<decltype(f)(double, int)>{} << "\n";
    std::cout << is_invokable<decltype(f)(double)>{} << "\n";
    std::cout << is_invokable<decltype(f(3.14))(int)>{} << "\n";
    decltype(std::declval<decltype((foo))>()(std::declval<double>(), std::declval<int>())) y = {3};
    (void)y;
	// std::cout << << "\n";
}