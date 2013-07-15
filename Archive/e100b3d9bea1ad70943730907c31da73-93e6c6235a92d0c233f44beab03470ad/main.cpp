#include <unordered_map>
#include <iostream>

template<typename Key>
class A {
public:
    std::unordered_map<Key, int> stuff;
public:
    A(std::initializer_list<std::pair<Key, int>> l): stuff(l.begin(), l.end()) {}
};

int main() {
    A<int> a = { {1, 1}, {2, 2}, {3, 3} };
    std::cout << a.stuff.size() << std::endl;
}