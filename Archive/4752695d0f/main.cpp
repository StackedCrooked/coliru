#include <iostream>

class Test
{
int arr[0];//why size is zero?
};

int main()
{
    Test t;
    std::cout << sizeof(t) << std::endl;
    
    return 0;
}