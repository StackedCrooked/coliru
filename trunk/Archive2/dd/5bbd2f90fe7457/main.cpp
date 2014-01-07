enum class E { e };
struct A { explicit constexpr operator const E() const noexcept { return E::e; } };

constexpr E e1{A{}};                      // Gcc: OK, Clang: Error
struct B { static constexpr E e2{A{}}; }; // Gcc: Error, Clang: Error
void f() { static constexpr E e3{A{}}; }  // Gcc: OK, Clang: Error

int main()
{
}
