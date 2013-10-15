#include <iostream>
#include <typeinfo>

template <typename T>
void what_is_my_type(const T&)
{
    std::cout << typeid(T).name() << std::endl;
}

int main()
{
    int arr[10];
    
    what_is_my_type(arr); // evaluates arr
}
