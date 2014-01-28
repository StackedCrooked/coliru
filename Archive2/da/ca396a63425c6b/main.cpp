namespace enum_paren_init {
    enum class E { e };
    struct A { explicit constexpr operator const E() const noexcept { return E::e; } };

    constexpr E e1(A{});                      // Gcc: OK, Clang: OK
    //struct B { static constexpr E e2(A{}); }; // Gcc: Error, Clang: Error
    void f() { static constexpr E e3(A{}); }  // Gcc: OK, Clang: OK
}

namespace struct_paren_init {
    struct S { constexpr S(){} constexpr S(const S&){}};
    struct A { explicit constexpr operator S() const noexcept { return S(); } };

    constexpr S s1(A{});                      // Gcc: OK, Clang: OK
    //struct B { static constexpr S s2(A{}); }; // Gcc: Error, Clang: Error
    void f() { static constexpr S s3(A{}); }  // Gcc: OK, Clang: OK
}

int main()
{
}
