#include <map>

    template<typename T>
    std::map<int, T> storage;
    
void some_func() {

    auto store = [](int key, const auto& value) { storage<int>.insert(key, value); };

    store(0, 2);
    store(1, "Hello"s);
    store(2, 0.7);

    // All three values are stored in a different map, according to their type. 
}