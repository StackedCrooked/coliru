#include <algorithm>
#include <memory>
#include <random>
#include <vector>

int main() {
    const int n = 10000;  // number of Objects to allocate
    
    std::mt19937 engine{std::random_device{}()};
    std::uniform_int_distribution<std::size_t> dist(1, 1000);

    std::vector<std::unique_ptr<char[]>> pointers;
    pointers.reserve(n);

    std::generate_n(std::back_inserter(pointers), n, [&]{
        return std::unique_ptr<char[]>(new char [dist(engine)]);
    });
}
