#include <iostream>
#include <string>
#include <vector>
#include <utility>

template<typename F, typename S>
std::ostream& operator<<(std::ostream& os, const std::pair<F, S>& t) {
    return os << '(' << t.first << ',' << t.second << ')';
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
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
        {1,0,0,0,1,0},
        {1,1,0,0,1,1},
        {1,0,0,0,0,0},
    };
    typedef std::vector<std::pair<unsigned int, unsigned int>> colonies;
    colonies left;
    colonies right;
    for (unsigned int y = 0; y < height; ++y) {
        colonies * vector = &left;
        for (unsigned int x = 0; x < width; ++x) {
            const unsigned int value = array[y][x];
            if (value == 0) {
                vector = &right;
            } else {
                vector->push_back(std::make_pair(y, x));
            }
        }
    }
    std::cout << "Right: " << std::endl << right << std::endl;
    std::cout << "Left: " << std::endl << left << std::endl;
}
