namespace A {
    int i;
    namespace B {
        namespace C {
            int i;
        }
        using namespace A::B::C;
        void f1() { i = 5; }        // OK, C::i visible in B and hides A::i
    }
    namespace D {
        using namespace B;
        using namespace C;
        void f2() { i = 5; }        // ambiguous, B::C::i or A::i?
    }
    void f3() {
        i = 5;                      // uses A::i
    }
}
void f4() {
    i = 5;                          // ill-formed; neither i is visible
}
