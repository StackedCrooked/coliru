#include <iostream>

template <typename T>
class A
{
public:
    static int i;
};

template <typename T>
int A<T>::i = 0;


int main()
{    
    A<float> a;
    a.i = 4;
    
    A<int> b;
    b.i = 3;
    
    std::cout << b.i << std::endl;
    return 0;
}