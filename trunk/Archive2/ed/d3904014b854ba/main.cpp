#include <map>

template<typename K, typename V>
std::map<K, V> storage; // not defined, intended

template<typename V>
std::map<int, V> storage<int, V>; // not defined, accidental

void some_func() {
    auto store = [](auto pair) { storage<int, decltype(pair.second)>.insert(pair); };

    store(std::pair<int, int>(0, 1));
    store(std::pair<int, std::string>(1, "Hello!"));
    store(std::pair<int, int>(2, 3));
}

int main()
{
}