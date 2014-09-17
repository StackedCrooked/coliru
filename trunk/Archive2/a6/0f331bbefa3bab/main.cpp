#include <cstddef>
using namespace std;

template<typename T, size_t S = T::noElems()>
struct C
{
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

struct Y
{
    struct Z
    {
        enum E { A, B, C };
        static constexpr size_t noElems() { return C+1; };
    };
    C<Z, Z::C+1> cyz; // this DOES compile

    C<Z> cyz2; // <--- this does NOT compile 
};

int main(){}
