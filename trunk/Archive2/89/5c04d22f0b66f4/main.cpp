#include <iostream>
class A {
public:
    A(int i) : x(i) { std::cout << "A(int)" << '\n'; }
    A() : x(1) { std::cout << "A()" << '\n'; }
    int x;
};


class B : private virtual A {           // Members A(int), A() and x in class A are accessible in B. Therefore the calls A(i) in B(int), and the default
                                        // constructor call supplied by the compiler in B(), A(), are valid calls in class B.
protected:
    B(int i) : A(i) { std::cout << "B(int)" << '\n'; }
    B() { std::cout << "B()" << '\n'; }
};


class C : public B {                    // But members A(int) and A() are NOT accessible in C and so, the compiler will NOT accept, for example, a
                                        // mem-initialized-id, like A(i), in C(int), or a mem-initializer-id, like A() in C(), below.
public:
    C(int i) : B(i) { std::cout << "C(int)" << '\n'; }
    C() : B() { std::cout << "C()" << '\n'; }
};


int main() {
    C c;                // This will print:
                          //
                          // A()
                          // B()
                          // C()
                          //
                          //  But A() is inaccessible in C, so this should not compile !


    C c1{1};            // This will print:
                        //
                        // A()              <-- Attention: A() is implicitly called here, as the call A(i) in B::B() is ignored by §12.6.2/7 !
                        //                                 But again, this is not correct, as A() is not accessible in class C.
                        // B(int)
                        // C(int)


}
