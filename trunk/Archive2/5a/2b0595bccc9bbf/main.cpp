#include <iostream>
#include <algorithm>
int main()
{
    int array[5] = {4,3,2};

    std::copy_backward(array, array+3, array+4);
    array[0] = 5;

    for(int n: array)
        std::cout << n << ' ';
}
