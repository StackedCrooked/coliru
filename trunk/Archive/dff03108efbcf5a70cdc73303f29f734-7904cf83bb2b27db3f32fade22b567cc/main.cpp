#include <iostream>

template <typename T, int SIZE>
void func(T (&arr)[SIZE])
{
    std::cout << SIZE << std::endl;
    
    for (auto i = 0; i < SIZE; ++i)
        std::cout << arr[i];
}

int main()
{
    char array[50] = "Hello!";
    func(array);
    return 0;
}