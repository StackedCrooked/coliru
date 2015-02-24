#include <iostream>
#include <cassert>
#include <typeinfo>

int main()
{
    using test1 = double(int);
    using test2 = double(*)(int);
    typedef double test3(int);
    typedef double (*test4)(int);
    
    test1 t1;
    test2 t2;
    test3 t3;
    test4 t4;
    
    assert(typeid(t1) == typeid(t3));
    assert(typeid(t2) == typeid(t4));
    assert(typeid(&t1) == typeid(t2));
    assert(typeid(&t3) == typeid(t4));
    
    std::cout << "All pass\n";
}
