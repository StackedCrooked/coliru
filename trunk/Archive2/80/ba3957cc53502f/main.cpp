class Base { protected: explicit Base(int); };
struct Derived: Base { Derived() : Base(42) { static_assert(!noexcept(Derived()), "Err"); } };
int main() try {
    Derived d;
} catch(...) {}
Base::Base(int b) { throw b; }