#include <utility>
#include <thread>

template <typename T>
struct f {
    void operator() (T& result) { result = 1;}
};

int main() {
    int x = 0;
    auto g = [](auto* result) { *result = 2; };

    std::thread(f<int>(), std::ref(x)).join();  // COMPILES
    std::thread(g, &x).join();         // FAILS TO COMPILE
    
    return x;
}