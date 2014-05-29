class Base { protected: Base(int); }; struct Derived: Base { Derived() : Base(42) { static_assert(!noexcept(Base(42)), "Err"); } };
int main() {
    Derived d;
}