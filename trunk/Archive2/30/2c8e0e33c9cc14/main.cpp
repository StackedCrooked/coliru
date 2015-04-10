#include <iostream>

int main()
{
    int arr[1] = { 0 };
    arr[2] = 2;
    std::cout << "No crash" << std::endl;
    return 0;
}