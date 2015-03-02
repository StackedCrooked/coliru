#include <cstdlib>
using std::size_t;

template <size_t N>
struct S
{
    union {
        int arr1[N];
        char arr2[sizeof(arr1)];
    };
};

int main()
{
    S<5> s;
}
