struct S 
{ 
    constexpr S() {}
    constexpr S(const S&) {}
};
struct A 
{ 
    explicit constexpr operator S() const noexcept { return S(); } 
};

constexpr auto s1 = S(A{});                      // Gcc: OK, Clang: Error
struct B { static constexpr auto s2= S(A{}); }; // Gcc: Error, Clang: Error
void f() { static constexpr auto s3= S(A{}); }  // Gcc: OK, Clang: Error

int main() {}
