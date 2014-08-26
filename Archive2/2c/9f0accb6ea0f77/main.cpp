#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    std::for_each(vec.begin(), vec.end(), [&os](T el) -> void {
        os << el << ' ';
    });
    return os;
}

int main()
{
    std::vector<std::string> words = {
        "420", "Blaze", "It"
    };
    std::cout << words << std::endl;
}
