#include <cstddef>

extern void* operator new(std::size_t n);

template<typename T>
T* create() { return new T(); }

int main() {
    auto result = 0;
    for (auto i = 0; i < 1000000; ++i) {
        result += (create<int>() != nullptr);
    }

    return result;
}
