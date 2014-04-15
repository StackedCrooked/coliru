#include <algorithm>
#include <iostream>
#include <string>

struct D;

class B {
    int _private {11};
    
    friend struct D;
};

struct D {
    B cp;
    D(B _cp) : cp(_cp) {}
    
    template <class FuncT>
    void verify_private(FuncT cb) { cb(cp._private); }
};

struct C : D {
    C(B b) : D(b) {}
    void verify() { D::verify_private([](int x){ std::cout << x << std::endl;  }); }
};

int main()
{
    B myB;
    C myC(myB);
    myC.verify();
}