namespace A {
      struct X;
      struct Y;
      void f(int);
      void g(X);
}
 
namespace B {
    void f(int i) {
        f(i);   // calls B::f (endless recursion)
    }
    void g(A::X x) {
        g(x);   // Error: ambiguous between B::g (ordinary lookup)
                //        and A::g (argument-dependent lookup)
    }
    void h(A::Y y) {
        h(y);   // calls B::h (endless recursion): ADL examines the A namespace
                // but finds no A::h, so only B::h from ordinary lookup is used
    }
}