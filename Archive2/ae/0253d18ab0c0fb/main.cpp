#include <functional>
#include <iostream>
#include <type_traits>
#include <utility>

template<class...Ts>
struct voider { using type = void; };
template<class...Ts>
using void_t = typename voider<Ts...>::type;
template<class T>
using decay_t = typename std::decay<T>::type;

template<class Sig,class=void>
struct is_invokable:std::false_type {};
template<class F, class... Ts>
struct is_invokable<
    F(Ts...),
    void_t<decltype(std::declval<F>()(std::declval<Ts>()...))>
>:std::true_type {};

#define RETURNS(...) decltype(__VA_ARGS__) { return (__VA_ARGS__); }

// Curry helper is sort of a manual lambda.  It captures a function and one argument
// It isn't written as a lambda so we can enable proper rvalue forwarding when it is
// used in an rvalue context, which is important when currying:
template<class F, class T>
struct curry_helper {
    F f;
    T t;

    template<class...Args>
    auto operator()(Args&&...args)const& ->
      RETURNS(f(t, std::forward<Args>(args)...))
    template<class...Args>
    auto operator()(Args&&...args)& ->
      RETURNS(f(t, std::forward<Args>(args)...))
    template<class...Args>
    auto operator()(Args&&...args)&& ->
      RETURNS(std::move(f)(std::move(t), std::forward<Args>(args)...))
};

template <typename> struct curry_t;

template <typename F, typename...Args>
auto apply_(std::true_type, F&& f, Args&&...args) ->
  RETURNS(std::forward<F>(f)(std::forward<Args>(args)...))

template <typename F, typename Arg>
auto apply_(std::false_type, F&& f, Arg&& arg) ->
  RETURNS(curry_t<curry_helper<F, decay_t<Arg>>>{{std::forward<F>(f), std::forward<Arg>(arg)}})

template <typename F, typename First, typename...Rest>
auto apply_(std::false_type, F&& f, First&& first, Rest&&...rest) ->
  RETURNS(curry_t<curry_helper<F, decay_t<First>>>{
    {std::forward<F>(f), std::forward<First>(first)}
  }(std::forward<Rest>(rest)...))

template <typename F, typename...Args>
auto apply(F&& f, Args&&...args) ->
  RETURNS(apply_(is_invokable<F(Args...)>{}, std::forward<F>(f), std::forward<Args>(args)...))

template<class F>
struct curry_t {
    F f;

    template<class...Args>
	auto operator()(Args&&...args)const& ->
      RETURNS(apply(f, std::forward<Args>(args)...))
    template<class...Args>
	auto operator()(Args&&...args)& ->
      RETURNS(apply(f, std::forward<Args>(args)...))
    template<class...Args>
	auto operator()(Args&&...args)&& ->
      RETURNS(apply(std::move(f), std::forward<Args>(args)...))
};

template<class F>
auto curry(F&& f) ->
  RETURNS(curry_t<decay_t<F>>{std::forward<F>(f)})

template<class F, class...Args>
auto curry(F&& f, Args&&...args) ->
  RETURNS(curry_t<decay_t<F>>{std::forward<F>(f)}(std::forward<Args>(args)...))

constexpr struct foo_t {
    double operator()(double x, int y, std::nullptr_t, std::nullptr_t)const{std::cout << "first\n"; return x*y;}
    char operator()(char c, int x)const{std::cout << "second\n"; return c+x;}
    void operator()(char const*s)const{std::cout << "hello " << s << "\n";}
} foo{};

struct print_t {
    template <typename T>
    auto operator()(std::ostream& os, T&& t) const ->
      RETURNS(curry(*this, std::ref(os << t)))
};

auto cout = curry(print_t{}, std::ref(std::cout));

int main() {
    cout("Hello,") (' ') ("World!") ('\n');
	auto f = curry(foo);
    // Call the 3rd overload:
    f("world");
    // testing the ability to "jump over" the second overload:
    cout(f(3.14,10,nullptr)(nullptr)) ('\n');
    // call the 2nd overload:
    auto x = f('a',2);
    cout(x) ("\n");
    // again:
    x = f('a')(2);
    cout(x) ("\n")
      (is_invokable<decltype(foo)(double, int)>{}) ("\n")
      (is_invokable<decltype(foo)(double)>{}) ("\n")
      (is_invokable<decltype(f)(double, int)>{}) ("\n")
      (is_invokable<decltype(f)(double)>{}) ("\n")
      (is_invokable<decltype(f(3.14))(int)>{}) ("\n");
    decltype(std::declval<decltype((foo))>()(std::declval<double>(), std::declval<int>())) y = {3};
    (void)y;
	// std::cout << << "\n";
}