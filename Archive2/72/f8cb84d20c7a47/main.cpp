#include <cstdint>
#include <iostream>
using namespace std;

template<typename T, size_t S =  T::noElems()>
struct C
{
    static constexpr size_t value = S;
};

struct X
{
    enum E { A, B, C };
    static constexpr size_t noElems() { return C+1; };
};

struct K
{
    C<X> cx; // this DOES compile
};

template<typename T = void>
struct Y
{
    struct Z
    {
        enum E { A, B, C };
        static constexpr size_t noElems() { return C+1; };
    };

    C<Z> cyz; // <--- Now it compiles
};

int main () { 
    cout << Y<>().cyz.value << endl;
}