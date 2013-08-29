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

struct data: private std::tuple<int, std::string> {
    using base_type = std::tuple<int, std::string>;
    
    using std::tuple<int, std::string>::tuple;
 
    template<int I, typename Data>
    using get_type = auto(Data&& d) -> decltype(std::get<I>(as_base<data, base_type>::F(std::forward<Data>(d))));
    
private:
    friend class as_base<data, base_type>;
    
    template<int I, typename Data>
    friend auto get(Data&& d)
    -> decltype( std::get<I>(as_base<data, base_type>::F(std::forward<Data>(d))) )
    { return std::get<I>(as_base<data, base_type>::F(std::forward<Data>(d))); }
};

template<int I, typename Data>
data::get_type<I, Data> get;

#include <iostream>

int main()
{
    data d { 42, "lol" };
    std::cout << get<0>(d) << '\n';
}