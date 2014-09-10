#include <random>
#include <iostream>


template<typename T>
T GetRandomNumber(T lower_bound, T upper_bound, typename std::enable_if<std::is_integral<T>::value>::type* = 0)
{
    static std::random_device random_dev;
    static std::mt19937 generator(random_dev());
    std::uniform_int_distribution<> distribution(lower_bound, upper_bound);
    return distribution(generator);
}


template<typename T>
T GetRandomNumber(T lower_bound, T upper_bound, typename std::enable_if<std::is_floating_point<T>::value>::type* = 0)
{
    static std::random_device random_dev;
    static std::mt19937 generator(random_dev());
    std::uniform_real_distribution<> distribution(lower_bound, upper_bound);
    return distribution(generator);
}


int main()
{
    std::cout << GetRandomNumber<int>(1, 100) << std::endl;
    std::cout << GetRandomNumber<double>(1, 100) << std::endl;
}
