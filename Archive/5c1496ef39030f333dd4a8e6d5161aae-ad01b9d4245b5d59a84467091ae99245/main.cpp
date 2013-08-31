#include <memory>

struct A {};

int main() {
    auto lambda = [](A* a) { delete a; };
    std::unique_ptr<A, decltype(lambda)> f(new A(), lambda);
}