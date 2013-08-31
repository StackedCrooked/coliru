#include <iostream>

int main()
{
    unsigned char arr[16];
    
    for (int i = 0; i != 8; ++i)
    {
        *((long long*)(&arr[i])) = i;
        std::cout << *((long long*)(&arr[i])) << std::endl;
    }
}