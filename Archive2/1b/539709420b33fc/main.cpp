#include <iostream>
#include <tuple>

template<typename T>
struct decompose_function_type;

template<typename R, typename... Args>
struct decompose_function_type<R(Args...)>
{
    using return_type = R;
    using parameter_types = std::tuple<Args...>;
};

template<typename T>
void print_type() { std::cout << __PRETTY_FUNCTION__ << "\n"; }

struct Int {};

Int const f() { return {}; }
int const g() { return {}; }

int main()
{
    auto& x = f();
    //auto& y = g(); // ill-formed
    
    print_type<decltype(f)>();
    print_type<decltype(g)>();
}