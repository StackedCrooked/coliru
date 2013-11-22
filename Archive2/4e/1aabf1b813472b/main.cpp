#include <initializer_list>

template<typename... Values>
void foo(std::initializer_list<Values>... args)
{
}

int main()
{
    foo({1}, {2, 3});
}
