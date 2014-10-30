#include <iostream>
#include <utility>

template<class T>struct voider{using type=void;};
template<class T>using void_t=typename voider<T>::type;

template<class Sig,class=void>
struct is_invokable:std::false_type {};
template<class F, class... Ts>
struct is_invokable<
    F(Ts...),
    void_t<decltype(std::declval<F>()(std::declval<Ts>()...))>
>:std::true_type {};

template<class F, class T>
struct curry_helper {
    F f;
    T t;
    template<class...Args>
    decltype(std::declval<F const&>()(std::declval<T const&>(), std::declval<Args>()...))
    operator()(Args&&...args)const&
    {
        return f(t, std::forward<Args>(args)...);
    }
    template<class...Args>
    decltype(std::declval<F>()(std::declval<T>(), std::declval<Args>()...))
    operator()(Args&&...args)&&
    {
        return std::move(f)(std::move(t), std::forward<Args>(args)...);
    }
};

template<class T> using type=T;

template<class F>
struct curry_t {
    F f;
	template<class Arg,class=typename std::enable_if<!is_invokable<type<F const&>(Arg)>::value, int>::type>
	auto operator()(Arg&& arg)const&
    {
		return curry_t< curry_helper<F, std::decay_t<Arg> >>{{ f, std::forward<Arg>(arg) }};
	}
	template<class... Args,class=typename std::enable_if<is_invokable<type<F const&>(Args...)>::value, int>::type>
	auto operator()(Args&&... args,...)const&
	{
		return f(std::forward<Args>(args)...);
	}
    template<class Arg,class=typename std::enable_if<!is_invokable<F(Arg)>::value, int>::type>
	auto operator()(Arg&& arg)&&
    {
		return curry_t< curry_helper<F, std::decay_t<Arg> >>{{ std::move(f), std::forward<Arg>(arg) }};
	}
	template<class... Args,class=typename std::enable_if<is_invokable<F(Args...)>::value, int>::type>
	auto operator()(Args&&... args,...)&&
	{
		return std::move(f)(std::forward<Args>(args)...);
	}
};

template<class F>
curry_t<typename std::decay<F>::type> curry( F&& f ) { return {std::forward<F>(f)}; }

static struct {
    int operator()(double, int)const{return 3;}
    char operator()(char, int)const{return 'a';}
} foo;

int main() {
    
	auto f = curry(foo);
    std::cout << f(3.14)('a') << "\n";
    auto x =  f('a',2);
    std::cout << x << "\n";
    std::cout << is_invokable<decltype(&foo)(double, int)>{} << "\n";
    std::cout << is_invokable<decltype(&foo)(double)>{} << "\n";
    std::cout << is_invokable<decltype(f)(double, int)>{} << "\n";
    std::cout << is_invokable<decltype(f)(double)>{} << "\n";
    std::cout << is_invokable<decltype(f(3.14))(int)>{} << "\n";
    decltype(std::declval<decltype((foo))>()(std::declval<double>(), std::declval<int>())) y = 3;
    (void)y;
	// std::cout << << "\n";
}