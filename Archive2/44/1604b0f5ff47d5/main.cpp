#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/ref.hpp>
#include <iostream>

class A {};


class B {
public:    
    B( A& ) {}
};


int main() {
    
    A a;
    boost::shared_ptr<B> b = boost::make_shared<B>( a );
    std::cout << "It works!" << std::endl;
}
