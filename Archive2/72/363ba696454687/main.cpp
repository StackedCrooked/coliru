#include <iostream>
#include <string>
#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec) {
        os << el << ' ';
    }
    return os;
}

int main()
{
    constexpr unsigned int width = 6;
    constexpr unsigned int height = 3;
    const unsigned int array[height][width] = {
        {9,2,2,2,9,2},
        {9,9,2,2,9,9},
        {9,2,2,2,2,2},
    };
    const unsigned int left_right[height][width] = {
        {1,0,0,0,1,0},
        {1,1,0,0,1,1},
        {1,0,0,0,0,0},
    };
    std::vector<unsigned int> left;
    std::vector<unsigned int> right;
    for (unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x) {
            if (left_right[y][x]) {
                left.emplace_back(array[y][x]);
            } else {
                right.emplace_back(array[y][x]);
            }
        }
    }
    std::cout << "Right: " << std::endl << right << std::endl;
    std::cout << "Left: " << std::endl << left << std::endl;
}
