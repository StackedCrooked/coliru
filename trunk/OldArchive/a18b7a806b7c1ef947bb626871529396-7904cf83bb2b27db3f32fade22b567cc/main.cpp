#include <iostream>

template <int SIZE>
void func(int (&arr)[SIZE])
{
    std::cout << SIZE << std::endl;
}

int main()
{
    int array[10];
    func(array);
    return 0;
}