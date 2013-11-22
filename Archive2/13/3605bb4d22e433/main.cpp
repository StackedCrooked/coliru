#include <initializer_list>

template<typename... Values>
void foo(std::initializer_list<Values>... args)
{
}

template<typename... Values>
void foo(Values&&... args)
{
}

int main()
{    
    foo(1, 2, 3, "hello", 'a');
    foo({1}, {2, 3});
}
