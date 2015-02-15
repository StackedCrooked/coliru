#include <iostream>
#include <functional>

template <typename T>
size_t getSize()
{
    return sizeof(T); 
}

// terminating case for T=double
template<>
size_t getSize<double>()
{
    return 100;
}

// terminating case for T=float
template<>
size_t getSize<float>()
{
    return 50;
}

// recursive case
template<class T, class U, class ...S>
size_t getSize()
{
    return getSize<T>() + getSize<U, S...>();
}

template <class ...T>
void print_function_arg_custom_size(std::function<void(T...)> f)
{
    size_t totalSize = 0;
    // get size recursively
    totalSize = getSize<T...>(); 

    std::cout << "totalSize: " << totalSize << std::endl;
}

void foo(uint8_t a, uint16_t b, uint32_t c, double d)
{
    // noop
}

int main()
{
    std::function<void(uint8_t, uint16_t, uint32_t, double)> f = foo;
    print_function_arg_custom_size<uint8_t, uint16_t, uint32_t, double>(f);

    return 0;
}