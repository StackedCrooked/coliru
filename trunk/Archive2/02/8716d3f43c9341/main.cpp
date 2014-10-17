#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

auto constexpr count = 8;

int main() {
    std::vector<int> numbers(count);

    std::cout << "Enter " << count << " integer values...\n";
    std::copy_n(std::istream_iterator<int>(std::cin), numbers.size(), numbers.begin());

    std::copy_if(numbers.begin(), numbers.end(),
                 std::ostream_iterator<int>(std::cout, "\n"),
                 [] (auto x) { return x > 21; });

    auto sum = std::accumulate(numbers.begin(), numbers.end(), 0);
    std::cout << "Sum: " << sum << '\n';

    return 0;
}