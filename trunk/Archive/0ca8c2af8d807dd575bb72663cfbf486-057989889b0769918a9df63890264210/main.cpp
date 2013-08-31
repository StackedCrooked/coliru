#include <type_traits>
#include <iostream>

template <int const* ptr>
void foo()
{

}

typedef void (*func_type)();

template <std::size_t O = 42>
void run_me()
{
    static int data;

    func_type f1 = foo<&data>;
    // auto f2 = foo<&data>;
}

int main()
{
    run_me();

    return 0;
}
