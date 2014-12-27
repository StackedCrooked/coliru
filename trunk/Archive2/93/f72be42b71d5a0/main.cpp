#include <iostream>
#include <type_traits>

template <typename Function>
auto call_function(Function&& f)
    -> typename std::result_of<Function&&()>::type
{
    return f();
}

template <typename Function, typename Class>
auto call_member_function(Function&& f, Class* instance)
    -> typename std::result_of<Function&&(Class*)>::type
{
    return (instance->*f)();
}

struct F
{
    void f() { std::cout << "F::f()" << std::endl; }
};

void f() { std::cout << "f()" << std::endl; }

int main()
{
    F instance;
    call_function(f);
    call_member_function(&F::f, &instance); 
}
