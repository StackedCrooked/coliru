

#include <iostream>
using namespace std;

template<typename T>
class D { 
    public: void foo() { T::foo(); }
};

class C {
    D<C> d;
    public: void test() { d.foo(); }
    
    static void foo() { cout << "baz";}
};

int main() {
    C c;
    c.test();
}