struct Base { void g(); };
struct Derived { void f(); };
typedef void (Derived::*dptr)();
typedef void (Base::*bptr)();
dptr func(); // Implemented in another TU
int main() {
    void (Base::*ptr)() = (bptr)func();
}