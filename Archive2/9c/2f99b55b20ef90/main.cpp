#include <iostream>

void h(int);
template <class T> void f2(T); 
namespace A {
  
    struct X {
        friend void f(X); // A::f(X) is a friend
        class Y {
            friend void g(); // A::g is a friend
            friend void h(int); // A::h is a friend
            // ::h not considered
            friend void f2<>(int); // ::f2<>(int) is a friend
            static const int i = 1000;
        };
    };
    // A::f, A::g and A::h are not visible here
    X x;
    void g() { f(x); } // definition of A::g
    void f(X) { /* ... */} // definition of A::f
    void h(int) { /* ... */ } // definition of A::h}
    template <class T> void f2(T t) { std::cout << X::Y::i << '\n'; }
    // A::f, A::g and A::h are visible here and known to be friends
}
using A::x;
void h() {
    A::f(x);
    //   A::X::f(x); // error: f is not a member of A::X
    //    A::X::Y::g(); // error: g is not a member of A::X::Y
}



int main()
{
    h();
    A::f2(1000);
}