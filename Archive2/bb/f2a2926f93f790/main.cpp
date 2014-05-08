    #include <iostream>
    using namespace std;
     
    class A {
        static const auto x = 1;
    public:
        friend void h(A&) {}
        friend void g() {}
        friend void k();
        A() {
            h(*this); // 0
            g();
            k();
        }
    };
     
     void k() { (void)A::x; }
 
    int main() {
        A a;
        h(a); // 1
        g();
        k();
    }