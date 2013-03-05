#include <iostream>
#include <type_traits>

template <typename T, typename POD=void>
class A;

template <typename T>
class A <T, typename std::enable_if<std::is_pod<T>::value>::type>
{
    //blah...
};

template <typename T>
class B;

template <typename T>
class B<const A<T>> : public A<T>
{
    public:
       B() { std::cout << "class B<const A<T>> version" << std::endl; }
};

template <typename T>
class B<A<T>> : public A<T>
{
public:
       B() { std::cout << "class B<A<T>> version" << std::endl; }
};

int main()
{
    B<A<int>>       x; //it chooses the second specialization
    B<const A<int>> y; //it chooses the first specialization
}