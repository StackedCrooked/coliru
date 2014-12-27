#include <iostream>
#include <type_traits>

template <typename Function, typename... Args>
auto call_function(Function&& f, Args&&... args)
    -> typename std::result_of<Function&&(Args&&...)>::type
{
    return std::forward<Function>(f)(std::forward<Args>(args)...);
}

template <typename Function, typename Class, typename... Args>
auto call_member_function(Function&& f, Class* instance, Args&&... args)
    -> typename std::result_of<Function&&(Class*, Args&&...)>::type
{
    return (instance->*f)(std::forward<Args>(args)...);
}

struct F
{
    int f(int a, char c) { std::cout << "F::f(int, char)" << std::endl; return 0; }
};

int f() { std::cout << "f()" << std::endl; return 0; }

int main()
{
    F instance;
    call_function(f);
    call_member_function(&F::f, &instance, 123, 'c'); 
}
