#include <tuple>
#include <string>
#include <iostream>
#include <utility>


template<typename... Ts>
struct tie_t
{
    std::tuple<Ts...> t;
    
    template<typename U>
    tie_t& operator=(U&& u)
    {
        t = as_tuple(std::forward<U>(u));
        return *this;
    }
};

template<typename... Ts>
tie_t<Ts&...> my_tie(Ts&... ts)
{
    return {std::tuple<Ts&...>{ts...}};
}


struct Foo {
    int a;
    std::string b;
};

template<typename S, typename D>
struct copy_r_t
{
    using type = D;
};
    template<typename S, typename D>
    struct copy_r_t<S&, D>
    {
        using type = D&;
    };
    template<typename S, typename D>
    struct copy_r_t<S&&, D>
    {
        using type = D&&;
    };
    
template<typename S, typename D>
struct copy_c_t
{
    using type = D;
};
    template<typename S, typename D>
    struct copy_c_t<S const, D>
    {
        using type = D const;
    };
    
template<typename S, typename D>
using copy_cvr = typename copy_r_t<S, typename copy_c_t< typename std::remove_reference<S>::type, D >::type>::type;

template<typename T, typename U>
copy_cvr<T&&, typename std::remove_reference<U>::type> forward_other(U&& u)
{
    return static_cast<copy_cvr<T&&,typename std::remove_reference<U>::type>>(u);
}

template<typename F, typename std::enable_if< std::is_same<typename std::decay<F>::type, Foo>::value >::type* = nullptr>
std::tuple<copy_cvr<F&&, int>, copy_cvr<F&&, std::string>>
as_tuple(F&& f)
{
    std::cout << __PRETTY_FUNCTION__ << "\n";
    return {std::tuple<copy_cvr<F&&, int>, copy_cvr<F&&, std::string>>{forward_other<F>(f.a), forward_other<F>(f.b)}};
}

template<typename T>
void print_type() { std::cout << __PRETTY_FUNCTION__ << "\n"; }

int main()
{
    long l; std::string s;
    my_tie(l, s) = Foo();
}