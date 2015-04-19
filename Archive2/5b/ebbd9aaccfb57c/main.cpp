namespace A {
    
    int i;                      // (3) Code introduced by compiler in place of `using namespace C;`below

    int i;                      //
    namespace C {               //
        int i;                  // (2) Code introduced by compiler in place of `using namespace B;` below
    }                           // 
    void f1() { i = 5; }        //

    int i;
    namespace B {
        int i;                  // (1) Code introduced by compiler in place of `using namespace A::B::C;` below

        namespace C {
            int i;
        }
        //using namespace A::B::C;
        void f1() { i = 5; }
    }
    namespace D {
        //using namespace B;
        //using namespace C;
        void f2() { i = 5; }
    }
    void f3() {
        i = 5;
    }
}
void f4() {
    i = 5;
}
