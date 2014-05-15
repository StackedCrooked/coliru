#include <iostream>
#include <string>
#include <vector>
#include <type_traits>

template <typename T, typename Enable = void>
struct blah_trait
{
    static const int case_no = 1;
};

template <>
struct blah_trait<int>
{
    static const int case_no = 2;
};

struct Base {};

template <typename T>
struct blah_trait<T, typename std::enable_if<std::is_base_of<Base, T>::value>::type>
{
    static const int case_no = 3;
};


template <typename T>
typename std::enable_if<blah_trait<T>::case_no == 1, void>::type print(const T * ptr)
{
    std::cout << "Case 1: " << *ptr << std::endl;
}
template <typename T>
typename std::enable_if<blah_trait<T>::case_no == 2, void>::type print(const T * ptr)
{
    std::cout << "Case 2: " << *ptr << std::endl;
}
template <typename T>
typename std::enable_if<blah_trait<T>::case_no == 3, void>::type print(const T * ptr)
{
    std::cout << "Case 3: " << std::endl;
}

struct B : Base {
};



int main()
{
    int foo = 5;
    double bar = 7.0;
    std::string z("ZZZ");
    B b;
    
    print(&foo);
    print(&bar);
    print(&z);
    print(&b);
}
