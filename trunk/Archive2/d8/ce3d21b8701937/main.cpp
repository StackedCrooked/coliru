#include <map>

template <typename T>
std::map<int, T> storage;

void some_func() {
    auto store = [&](auto pair) { storage<decltype(pair.second)>.insert(pair); };

    store(std::pair<int, int>(0, 1));
    store(std::pair<int, std::string>(1, "Hello!"));
    store(std::pair<int, int>(2, 3));
}

int main()
{
}