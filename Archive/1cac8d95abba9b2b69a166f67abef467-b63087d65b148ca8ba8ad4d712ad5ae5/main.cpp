#include <iostream>


#define TRACE std::cout << __FILE__ << ":" << __LINE__ << "\t" << __PRETTY_FUNCTION__ << std::endl;


struct Lock {
    Lock() { TRACE }    
    ~Lock() { TRACE }
};


struct B {
    B(){}
    B(const B&) { TRACE } // print if copy constructor is called
};

struct A {    
    B get_b() const {
        TRACE
        Lock lock;
        return b;
    }
    
    B b;
};


int main()
{
    A a;
    a.get_b();    
}