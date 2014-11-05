#include <boost/type_traits.hpp>
#include <iostream>
#include <typeinfo>

int main () {
    typedef const char* arf;
    typedef typename boost::remove_cv<arf>::type woof;
    
    std::cout << typeid(arf).name() << std::endl;
    std::cout << typeid(woof).name() << std::endl;
}