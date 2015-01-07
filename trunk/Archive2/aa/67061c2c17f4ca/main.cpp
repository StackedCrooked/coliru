#include <iostream>

template<typename R, class...A> 
R (*trap_gen(R(*f)(A...)))(A...)
{
    static auto g = f;

    return [](A... a) 
    {
        try {
            return g(a...);
        } catch (...) {
            return std::is_integral<R>::value ? static_cast<R>(42)
                                              : static_cast<R>(3.14); 
        }
    };
}

int add(int a, int b)
{
    return a+b;
}

int mul(int a, int b)
{
    return a*b;
}

int main()
{
    int(*f)(int, int) = trap_gen<>(add);
    std::cout << f(2, 3) << std::endl;
    
    int(*f2)(int, int) = trap_gen<>(mul);
    std::cout << mul(2, 3) << " == " << f2(2, 3) << "?" << std::endl; // should be 6
}
