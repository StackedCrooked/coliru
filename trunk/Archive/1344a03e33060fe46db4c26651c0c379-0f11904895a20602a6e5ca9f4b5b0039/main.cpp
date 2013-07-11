#include <memory>
#include <cstdlib>

namespace so {
    std::unique_ptr<void, void(*)(void*)> malloc(std::size_t n) {
        return { std::malloc(n), std::free };
    }
}

int main() {
    auto p = so::malloc(100);
}