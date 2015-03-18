#include <iostream>
#include <string>


template<class T> class concat {};

template<> class concat<std::string>
{
public:
    std::string operator()(const std::string& a, const std::string& b)
    {
        return a + b;
    }
};

template<> class concat<int>
{
public:
    int operator()(int a, int b)
    {
        return a + b;
    }
};

template<class T> void print_functor( T a, T b)
{
    std::cout << concat<T>()(a, b) << std::endl;
}

int main()
{
    std::cout << concat<std::string>()("hello", " world") << std::endl;
    std::cout << concat<int>()(1, 3)                      << std::endl;
    
    print_functor<int>(7, 9);
    print_functor<std::string>("uai", " so");
    
    return 0;
}