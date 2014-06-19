#include <iostream>

int fun(int input)
{
    if (input < 0) throw "something to throw";
    return input;
}

template <typename F, typename...Args>
static auto HandledCall(F&& function, Args...args)
-> decltype(std::forward<F>(function)(std::forward<Args>(args)...))
{
    try
    {
        return std::forward<F>(function)(std::forward<Args>(args)...);
    }
    catch(...)
    {
        return {};
    }
}

int main() {
    std::cout << HandledCall(fun,1) << std::endl; // this should return 1
    std::cout << HandledCall(fun,-1) << std::endl; // this should return 0      
}
