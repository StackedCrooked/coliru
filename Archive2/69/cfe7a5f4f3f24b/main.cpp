
#include <algorithm>
#include <iostream>

int main()
{
    int* arr = new int[5] {1, 2, 3, 2, 1};
    int* end = arr + 5;
    end = std::remove(arr, end, 2);
    for(int* i = arr; i != end; ++i)
        std::cout << *i << ' ';
}