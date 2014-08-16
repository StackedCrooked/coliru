#include <array>
#include <cstdint>
#include <future>
#include <iostream>
#include <vector>
#include <tuple>
#include <type_traits>

template <typename Fut, typename Work>
auto then(Fut f, Work w) -> std::shared_future<decltype(w(f.get()))>
{
    return std::async([=]{ w(f.get()); });
}

std::shared_future<int> sum(int a, int b)
{
    return std::async([](int a, int b) { return a + b; }, a, b);
}

int main() {
    then(sum(40, 2), [](int n) {std::cout << "Sum is " << n << std::endl;}).wait();
    return 0;
}
