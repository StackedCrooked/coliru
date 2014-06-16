#include <iostream>
#include <cstdint>
#include <type_traits>

template <typename T>
struct disable
{ static bool constexpr const value{ false }; };

template <typename T, typename E = void>
struct work
{ static_assert(disable<T>::value, "Invalid type for work"); };

template <typename T>
struct work<T, typename std::enable_if<std::is_integral<T>::value>::type>
{
    void bar()
    { std::cout << "working on an integer" << std::endl; }
};

template <typename T>
struct work<T, typename std::enable_if<std::is_floating_point<T>::value>::type>
{
    void bar()
    { std::cout << "working on a float" << std::endl; }
};

int main()
{
    work<int64_t>().bar();
    work<double>().bar();
    //work<char*>().bar(); // statically fails
}