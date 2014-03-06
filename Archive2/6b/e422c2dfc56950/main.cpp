#include <iostream>

using namespace std;

struct A
{
    static constexpr size_t L = 4;

    template <typename T>
    void member_ref(T&& x) { cout << std::forward<T>(x) << endl; }

    template <typename T>
    void member_val(T x) { cout << x << endl; }

};

constexpr size_t A::L;

template <typename T>
void ref(T&& x) { cout << std::forward<T>(x) << endl; }

template <typename T>
void val(T x) { cout << x << endl; }

int main ()
{
    A().member_ref(A::L);  // Clang: linker error: undefined reference to `A::L'
    A().member_val(A::L);  // fine (prints 4)
    ref(A::L);             // Clang: compiles/links fine, no output
    val(A::L);             // fine (prints 4)
}