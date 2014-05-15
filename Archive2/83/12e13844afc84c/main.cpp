#include <iostream>
#include <type_traits>
#include <typeinfo>

template<typename T>
using Remove_cv_ref = std::remove_cv<typename std::remove_reference<T>::type>;
    
template<typename T>
using Remove_ref_cv = std::remove_reference<typename std::remove_cv<T>::type>;
int main()
{
    //std::cout << std::is_same<typename Remove_cv_ref<const int&>::type, int>::value;
    //std::cout << std::is_same<typename Remove_ref_cv<const int&>::type, int>::value;
    int negative = -1;
    int *ptr = reinterpret_cast<int*>(negative);
    std::cout << (0 > ptr) << ptr << std::endl;
    std::cout << typeid(decltype(1U + 1)).name() << std::endl;
    std::cout << typeid(decltype(1 + 1U)).name() << std::endl;
    std::cout << typeid(decltype(1U + 1U)).name() << std::endl;
    std::cout << typeid(decltype(1 + 1)).name() << std::endl;
}
