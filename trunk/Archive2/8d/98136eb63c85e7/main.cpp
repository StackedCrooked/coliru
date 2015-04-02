#include <iostream>

template <typename T>
class A
{
public:
    static int i;
};

template <typename T>
int S<T>::i = 0;


int main()
{    
    A<float>::i = 4;
    A<int>::i = 3;
    
    std::cout << A<float>::i << std::endl;
    return 0;
}