#include <iostream>
#include <type_traits>
#include <typeinfo>

template<typename T>
using Remove_cv_ref = std::remove_cv<typename std::remove_reference<T>::type>;
    
template<typename T>
using Remove_ref_cv = std::remove_reference<typename std::remove_cv<T>::type>;
static int a = 1666;
int main()
{
    //std::cout << std::is_same<typename Remove_cv_ref<const int&>::type, int>::value;
    //std::cout << std::is_same<typename Remove_ref_cv<const int&>::type, int>::value;
    std::cout << (0 > &a) << &a << std::endl;
}
