#include <string>

template<typename T>
struct Outer
{
    struct Inner {};
};

template<typename T>
struct Traits;

template<typename T>
struct Traits< typename Outer<T>::Inner >
{
};

int main()
{
}