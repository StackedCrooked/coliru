#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <random>
#include <vector>

template <typename T>
struct my_allocator {
  using value_type = T;
  T* allocate(std::size_t n) {
    std::cout << "allocate(" << n << ")\n";
    return (T*)std::malloc(n * sizeof(T));
  }
  void deallocate(T* ptr, std::size_t n) {
    std::cout << "deallocate(" << ptr << ", " << n << ")\n";
    std::free(ptr);
  }
};

int main() {
    auto engine = std::mt19937_64{std::random_device{}()};
    auto dist = std::uniform_int_distribution<int>{};
    auto rng = [&]{return dist(engine);};

    // vector.
    auto c = std::vector<int, my_allocator<int>>{};
    std::generate_n(std::back_inserter(c), 1024, rng);
}
