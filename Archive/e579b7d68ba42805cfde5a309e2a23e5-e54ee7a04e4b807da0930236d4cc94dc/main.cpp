template<typename T, typename U>
struct is_same
{
    static const bool value = false;
};

template<typename T>
struct is_same<T, T>
{
    static const bool value = true;
};

template<typename T, typename U>
bool eqTypes() { return is_same<T, U>::value; }

#include <iostream>
#include <iomanip>

int main()
{
    std::cout << std::boolalpha;
    std::cout << eqTypes<int, double>() << std::endl;
    std::cout << eqTypes<int, int>() << std::endl;
}
