#include <iostream>

template<typename T, typename F>
T Sum(T arg, F f)
{
    return f(arg);
}

template<typename T>
T Callback(T arg)
{
    std::cout << "Callback is called" << std::endl;
    return arg;
}

auto Callback2 = [](auto arg)
{
    std::cout << "Callback2, a generic lambda, is called" << std::endl;
    return arg;
};

int main()
{
    std::cout << Sum(10.2f, Callback<float>) << std::endl;
    std::cout << Sum(10.2f, Callback2) << std::endl;
    std::cout << Sum(10.2f, [](auto arg) {
        std::cout << "An in-plance generic lambda is called" << std::endl;
        return arg;
    }) << std::endl;

    getchar();
    return 0;
}