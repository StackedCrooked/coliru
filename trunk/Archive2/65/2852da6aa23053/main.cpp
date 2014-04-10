#include <type_traits>
#include <iostream>


template <typename T>
struct foo
{ 
    static void my_func() 
    {
        static_assert(std::is_floating_point<T>::value, "I take only floats");
    }
}; 

template <>
struct foo<float>
{
    static void my_func() 
    {
        std::cout << "good" << std::endl;
    }
};

int main() 
{
    foo<float>::my_func();
}
