#include <initializer_list>

template<class T>
void foo(T&&) {}

int main()
{
    foo({1,2,3});
}