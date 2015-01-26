#include <utility>
#include <thread>

template <typename T>
struct f {
    void operator() (T& result) { result = 1;}
};

int main() {
    int x = 0;
    auto g = [](auto& result) { result = 1; };

    std::thread(f<int>(), std::ref(x));  // COMPILES
    std::thread(g, std::ref(x));         // FAILS TO COMPILE
    
    //g(std::ref(x));
}