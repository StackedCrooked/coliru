#include <list>
#include <iostream>

int main() {
    std::list<int> l {0, 1, 5, 5, 3, 5};
    auto ret = l.equal_range(5);
    for (auto it = ret.first; it != ret.second && it != l.end(); ++it)
        std::cout << *it << ' ';
    return 0;
}