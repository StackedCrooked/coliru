#include <thread>

template <typename T>
struct f {
    void operator() (T& result) { result = 1;}
};

int main() {
    int x = 0;
    auto g = [](auto& result) { result = 1; };

    std::thread([&]{ return f<int>{}(x); });
    std::thread([&]{ return g(x); });
}
