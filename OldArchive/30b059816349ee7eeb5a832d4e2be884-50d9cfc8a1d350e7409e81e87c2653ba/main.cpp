#include <algorithm>
#include <array>
#include <vector>
#include <iostream>

int main()
{
    {
        int array1[8] = {1, 2};
        int array2[8] = {3, 4};
        std::cout << "Before (int[]): " << array1[0] << std::endl;
        array1[0] = std::move(array2[0]);
        std::cout << "After (int[]): " << array1[0] << std::endl;
    }
    {
        std::array<int, 8> array1 = {1, 2};
        std::array<int, 8> array2 = {3, 4};
        std::cout << "Before (std::array): " << array1[0] << std::endl;
        array1[0] = std::move(array2[0]);
        std::cout << "After (std::array): " << array1[0] << std::endl;
    }
    {
        std::vector<int> array1 = {1, 2};
        std::vector<int> array2 = {3, 4};
        std::cout << "Before (std::vector): " << array1[0] << std::endl;
        array1[0] = std::move(array2[0]);
        std::cout << "After (std::vector): " << array1[0] << std::endl;
    }    
    return 0;
}
