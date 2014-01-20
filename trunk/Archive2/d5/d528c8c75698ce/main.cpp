#include <map>

template <typename T>
std::map<int, T> storage;

void some_func() {
    auto store = [&](auto pair) { storage<T>.insert(pair); };

    store(std::pair<int, int>(0, 1));
    store(std::pair<int, int>(1, 2));
    store(std::pair<int, int>(2, 3));
}