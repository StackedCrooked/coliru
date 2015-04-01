#include <iostream>
#include <type_traits>

template<class... Args>
struct highest_type;

template<class A, class... Args>
struct highest_type<A, Args...>
{
    using type = A;
};

template<class A, class B, class... Args>
struct highest_type<A, B, Args...>
{
    using type = typename highest_type<typename std::conditional<(sizeof(A) > sizeof(B)), A, B>::type, Args...>::type;
};



int main()
{
    using size10 = std::aligned_storage<10, 1>::type;
    using size20 = std::aligned_storage<20, 1>::type;
    using size30 = std::aligned_storage<30, 1>::type;
    using size40 = std::aligned_storage<40, 1>::type;
    using size50 = std::aligned_storage<50, 1>::type;
    
    std::cout << sizeof(highest_type<size10, size20, size30, size40, size50>::type) << std::endl;
    std::cout << sizeof(highest_type<size40, size50, size30, size10, size20>::type) << std::endl;
    std::cout << sizeof(highest_type<size50, size20, size30, size40, size10>::type) << std::endl;
    std::cout << sizeof(highest_type<size30, size40, size10, size20, size50>::type) << std::endl;
}