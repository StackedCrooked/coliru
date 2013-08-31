#include <iostream>
#include <boost/optional.hpp>

using boost::optional;
using std::cout;
using std::endl;

int foo(optional<int> a, optional<int> b) {
    int a_ = a.get_value_or(0);
    int b_ = b.get_value_or(0);
    return a_+b_;
}

int main () {
    
    cout << foo(1,2);
    cout << foo(boost::none, 2);
    cout << foo(3, boost::none);
    
    int(*p)(int, int) = foo;
    
    return 0;
}