#include <iostream>
    using namespace std;

    struct Base {
    void f(int){
        cout << "\n f(base) is called" ;
    }
    };
    struct Derived : Base {
    using Base::f ;    //  using-declarations  but still Drived function is called
    void f(int){
        cout << "\n f(Drived) is called" ;
    }
    };
    void use(Derived d)
    {

    d.f(1);     // calls Derived::f
    Base& br = d ;
    br.f(1);        // calls Base::f
    }

    int main() {

        Derived d;
        use (d);
        return 0;
    }