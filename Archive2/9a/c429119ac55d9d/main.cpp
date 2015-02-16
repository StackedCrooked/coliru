#include <map>
#include <type_traits>

    template<typename T>
    std::map<int, T> storage;
    
void some_func() {

    auto store = [](int key, const auto& value) { storage<typename std::remove_const<typename std::remove_reference<decltype(value)>::type>::type>.insert(std::make_pair(key, value)); };

    store(0, 2);
    store(1, std::string("Hello"));
    store(2, 0.7);

    // All three values are stored in a different map, according to their type. 
}