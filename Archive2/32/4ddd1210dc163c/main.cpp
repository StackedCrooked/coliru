#include <iostream>

int main()
{
    int arr[4] = { 1, 2 };
    for(int i : arr)
    {
        std::cout << i << " ";
    }
    
    return 0;
}