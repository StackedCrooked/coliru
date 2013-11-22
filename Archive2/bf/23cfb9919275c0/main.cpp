#include <algorithm>
#include <cstddef>
#include <functional>
#include <iterator>
#include <iostream>
#include <string>

template<typename RandomIt, typename Comparator>
std::size_t permutation_index(RandomIt begin, RandomIt end, Comparator comparator) {
    std::size_t k = std::distance(begin, end);

    std::size_t radix(1);
    for (std::size_t i = 2; i < k; ++i) {
        radix *= i;
    }

    std::size_t result = 0;
    for (; begin != end; ++begin) {
        result += radix * std::count_if(begin, end, std::bind(comparator, std::placeholders::_1, *begin));
        if (begin + 1 != end) {
            radix /= std::distance(begin, end) - 1;
        }
    }

    return result;
}

template<typename RandomIt, typename Comparator>
void nth_permutation(RandomIt begin, RandomIt end, std::size_t n, Comparator comparator) {
    std::sort(begin, end, comparator);

    std::size_t k = std::distance(begin, end);

    std::size_t radix = 1;
    for (std::size_t i = 2; i < k; ++i) {
        radix *= i;
    }

    for (std::size_t i = 0; i < k; ++i) {
        std::size_t digit = n / radix;

        std::rotate(begin, begin + digit, begin + digit + 1);

        ++begin;

        n %= radix;

        if (i + 1 != k) {
            radix /= k - i - 1;
        }
    }
}

int main() {
    std::string sequence("Hello, world!");

    auto n = permutation_index(sequence.begin(), sequence.end(), std::less<char>());
    nth_permutation(sequence.begin(), sequence.end(), n, std::less<char>());

    std::cout << sequence << '\n';

    return 0;
}
