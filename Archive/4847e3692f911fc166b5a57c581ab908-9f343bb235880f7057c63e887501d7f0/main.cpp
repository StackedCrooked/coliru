#include <cstdio>

template<class X, int N>
struct Bar {
    Bar( ) { printf("general"); } 
};

template <>
Bar<class X,2>::Bar( ) { printf("spec"); }

int main()
{
    Bar<int, 2> b;
}