#include <thread>

int main() {
    int x = 0;
    auto g = [](auto&& result) { result = 1; };

    std::thread([&]{ return g(x); });
    std::thread([&]{ return g(std::move(x)); });
}
