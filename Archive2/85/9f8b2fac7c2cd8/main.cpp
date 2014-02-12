#include <initializer_list>

template<class T>
void foo(T&&) {}

int main()
{
    foo(std::initializer_list<int>{1,2,3});
    foo({1,2,3});
}