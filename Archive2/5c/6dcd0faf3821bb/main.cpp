class Base { protected: explicit Base(int); };
struct Derived: Base { Derived() noexcept(noexcept(Base(42))) : Base(42) { static_assert(!noexcept(Derived()), "Err"); } };
int main() {
    Derived d;
}