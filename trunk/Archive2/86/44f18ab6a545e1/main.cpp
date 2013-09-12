#include <iostream>
#include <type_traits>
#include <utility>

template<typename T, size_t N>
struct array_checker
{
    constexpr bool test(T (&&arr)[3]) const
    {
        return true;
    }
    
    constexpr bool test(...) const
    {
        return false;
    }
};

int main()
{
    //std::remove_reference<decltype(std::declval< array_size_checker >().prova())>::type nn = {1,2,3,4};
    //std::cout << std::extent<decltype(std::declval< array_size_checker<7> >().prova())>::value << std::endl;
    //std::cout << std::extent<decltype(std::declval< array_size_checker >().prova())>::value << std::endl;
    //decltype({1,2,3}) p;
    std::cout << array_checker<int, 4>().test({1,2,3,4}) << std::endl;
}
