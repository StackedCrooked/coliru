#include <functional>
#include <iomanip>
#include <iostream>


template <class T>
struct NonDeduced
{
  typedef T type;
};

template <class T>
void f(const T& v, const std::function< bool( const typename NonDeduced<T>::type& ) >& validator )
{
    if (validator(v))
        std::cout << v;
}

void f(const bool& v)
{
    std::cout << std::boolalpha << v;
}

int main()
{
    f(5, [](const int& a){ return a != 0; });
    f(true);
}