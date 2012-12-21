#include <iostream>
#include <string>

#define TRACE puts(__FUNCTION__);

template<typename T, unsigned N>
struct A
{
    A<T, N - 1> operator->() const
    {
        std::cout << "N: " << N << std::endl;
        return A<T, N - 1>();
    }

    T t;
};

template<typename T>
struct A<T, 0>
{
    const T * operator->() const
    {
        std::cout << "N: " << 0 << std::endl;
        return &t;
    }

    T t;
};

int main()
{
    A<std::string, 10> a;
    a->size();
}
