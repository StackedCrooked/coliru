#include <tuple>
#include <string>

/* Reusable */
template<typename Derived, typename Base>
struct as_base {
    template<typename T>
    static T&& F(T&& t)
    { return std::forward<T>(t); }
    
    static Base& F(Derived& d)
    { return d; }
    
    static Base const& F(Derived const& d)
    { return d; }
    
    static Base&& F(Derived&& d)
    { return std::move(d); }
};

struct data;

template<int I, typename Data>
auto get(Data&& d)
-> decltype( std::get<I>(as_base<data, std::tuple<int, std::string>>::F(std::forward<Data>(d))) );

struct data: private std::tuple<int, std::string> {
    using base_type = std::tuple<int, std::string>;
    
    using std::tuple<int, std::string>::tuple;
    
private:
    friend class as_base<data, base_type>;
    
    template<int I, typename Data>
    friend auto get(Data&& d)
    -> decltype( std::get<I>(as_base<data, std::tuple<int, std::string>>::F(std::forward<Data>(d))) )
    { return std::get<I>(as_base<data, std::tuple<int, std::string>>::F(std::forward<Data>(d))); }
    
    template<typename... T>
    friend auto tuple_cat(T&&... t)
    -> decltype( std::tuple_cat(as_base<data, base_type>::F(std::forward<T>(t))...) )
    { return std::tuple_cat(as_base<data, base_type>::F(std::forward<T>(t))...); }
};

#include <iostream>

int main()
{
    data d { 42, "lol" };
    std::cout << get<1>(d) << '\n';
    std::cout << std::get<0>(tuple_cat(d, std::make_tuple(1, 2, 3))) << '\n';
}