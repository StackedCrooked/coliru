#include <iterator>

namespace foo {
    template<typename T, int N> void bar(T(&p)[N]) {
    }
}

int main()
{
    int* p;
    int arr[5];
    foo::bar(arr);
    foo::bar(p);
}