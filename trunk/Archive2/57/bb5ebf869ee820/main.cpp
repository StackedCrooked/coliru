#include <unordered_map>
#include <functional>
#include <utility>
#include <cstddef>

template <typename T>
struct my_allocator {
    using value_type = T;

    T* allocate(std::size_t) { return nullptr; }
    void deallocate(T*, std::size_t) {}
};

int main() {
    using map_type = std::unordered_map<int, double, std::hash<int>, std::equal_to<int>, my_allocator<std::pair<const int, double>>>;

    map_type m { { 1, 1. } , { 2, 2. } };
}

