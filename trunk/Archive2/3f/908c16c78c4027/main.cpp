#include <thread>

template <typename T>
struct f {
    void operator() (T& result) { result = 1;}
};

int main() {
    auto g = [](auto& result) { result = 1; };
    int x = 0;

    std::thread(f<int>{}, std::ref(x)).join();     // COMPILES
    std::thread(std::bind(g, std::ref(x))).join(); // COMPILES
}
