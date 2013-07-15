#include <unordered_map>

template<typename Key>
class A {
    std::unordered_map<Key, int> stuff;
public:
    A(std::initializer_list<std::unordered_map<Key, int>> l): stuff(l.begin(), l.end()) {}
};

int main() {
    A<int> a = { {1, 1}, {2, 2}, {3, 3} };
}