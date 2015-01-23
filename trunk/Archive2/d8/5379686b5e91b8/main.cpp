#include <utility>

template <class F, class... Args>
void for_each_argument(F f, Args&&... args) {
    [](...){}((f(std::forward<Args>(args)), 0)...);
}

#include <iostream>

int main()
{
    for_each_argument([](int i) { std::cout << i << ", "; }, 1, 2, 3, 4);
    std::cout << '\n';
}

