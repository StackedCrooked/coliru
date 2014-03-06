#include <iostream>

using namespace std;

template<class = void>
struct A_
{
    static constexpr size_t L = 4;

    template <typename T>
    void member_ref(T&& x) { cout << std::forward<T>(x) << endl; }

    template <typename T>
    void member_val(T x) { cout << x << endl; }

};

template<class T>
constexpr size_t A_<T>::L;

using A = A_<>;

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