#include <iostream>

struct A {
    virtual ~A() {}
    virtual int bar() = 0;
};

struct B {
    int bar() {return 1;}
};

struct C {
    int bar() {return 2;}
};


struct D {
    template <class T>
    static int foo() {
        T a;
        return a.bar();
    }
};


template<class T, class U>
int callFoo() {
    return T::foo<U> (); ///error: expected primary-expression before '>' token
}


int main(int argc, char** argv) {
        std::cout << D::foo<B>() << std::endl; //This works of course
        std::cout << D::foo<C>() << std::endl; //This works of course
        std::cout << callFoo<D,B>() << std::endl;
        std::cout << callFoo<D,C>() << std::endl;
    }

