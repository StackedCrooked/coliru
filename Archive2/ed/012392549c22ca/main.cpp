#include <boost/type_traits.hpp>
#include <iostream>
#include <typeinfo>

int main () {
    typedef char * const arf;
    typedef typename boost::remove_cv<arf>::type woof;
    
    std::cout << std::is_same<arf, woof>::value << std::endl;
}