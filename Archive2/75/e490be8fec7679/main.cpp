#include <type_traits>
#include <utility>
#include <string>
#include <vector>
#include <iostream>

template<typename F, typename... Args>
auto HandledCall(F&& func, Args&&... args)
    -> typename std::result_of<F(Args...)>::type
{
    try {
        return std::forward<F>(func)(std::forward<Args>(args)...);
    } catch(...) {
        return {};
    }
}

std::string foo(std::vector<int>) { return ""; }
void bar() {}

int fun(int input)
{
    return input;
}

int main()
{
    static_assert(std::is_same<decltype(HandledCall(foo, std::vector<int>{})), std::string>::value, "Oops1");
    static_assert(std::is_same<decltype(HandledCall(bar)), void>::value, "Oops2");
    static_assert(std::is_same<decltype(fun(1)), int>::value, "Oops3");
    
    std::cout << HandledCall(fun,1) << std::endl; // this should return 1
    std::cout << HandledCall(fun,-1) << std::endl; // this should return 0
}
