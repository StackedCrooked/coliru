#include <iostream>
#include <vector>

template <typename ContainerType, typename ResultType = double>
ResultType avg(const ContainerType c) {
    typename ContainerType::value_type total{};
    for (auto v : c) {
        total += v;
    }
    return total / static_cast<ResultType>(c.size());
}


int main() {
    std::cout << std::fixed;
    std::cout << "Average of some ints:    " << avg(std::vector<int>{5, 12, 136, 999, 17}) << '\n';
    std::cout << "Average of some doubles: " << avg(std::vector<double>{1240.54124, 25231.2993, 2839928.22407, 2398.234}) << '\n';
}