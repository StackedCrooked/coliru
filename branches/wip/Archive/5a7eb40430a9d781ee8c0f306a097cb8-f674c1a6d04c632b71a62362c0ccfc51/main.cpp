#include <boost/variant.hpp>
#include <iostream>
 
template<typename T, typename Variant>
struct convertible_to {
    Variant &vt;
    
    operator T&() {
        return boost::get<T>(vt);
    }
};
 
template<typename... Types>
struct variant_wrapper : public convertible_to<Types, boost::variant<Types...>>... {
    using variant_type = boost::variant<Types...>;
    
    variant_wrapper(variant_type &v) 
    : convertible_to<Types, variant_type>{v}...
    {
        
    }
};
 
// example class
struct test {
    typedef boost::variant<double, long int, std::string> ConfigVariant;
    typedef variant_wrapper<double, long int, std::string> wrapper_type;
    
    ConfigVariant data;
    
    test() {
        boost::get<double>(data) = 15.0;
    }
    
    wrapper_type operator[](size_t) {
        return wrapper_type(data);
    }
};
 
int main() {
    test c;
    double i = c[0];
    std::cout << i << std::endl;
}