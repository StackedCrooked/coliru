#include <iostream>
#include <map>

std::map<int, int> myset;

int main() {

    myset.emplace(0, 5);
    myset.emplace(1, 0);
    myset.emplace(1, 1);
    myset.erase(0);

    std::cout << myset.size() << std::endl;
    for (auto i : myset)
        std::cout << "(" << i.first << "," << i.second << ")" << std::endl;
    return 0;
}
