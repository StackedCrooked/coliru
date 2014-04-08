#include <iostream>

int main()
{
    int arr[5];
    arr[0] = 100;
    std::cerr << "The value at index 0 is: " << arr[0] << "\n";
    // Now for the interesting part!
    1[arr] = 10;
    std::cerr << "The value at index 1 is: " << arr[1] << "\n";
}
