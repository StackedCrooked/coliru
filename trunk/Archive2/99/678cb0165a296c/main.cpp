#include <iostream>

int main()
{
    char a[5] = {'h', 'e', 'l', 'l', 'o'};
    void *ptr;
    ptr = &a[0];
    for(int i = 0; i < 5; i++)
    {
        std::cout << ptr << std::endl;
        ptr++;
    }
}