#include <algorithm>
#include <iostream>
#include <vector>

std::size_t compute_box_combinaison(std::vector<std::size_t> v, std::size_t total)
{
    if (v.size() < 2) {
        return 0;
    }
    std::size_t res = 0;

    std::sort(v.begin(), v.end());

    auto low = v.begin();
    auto high = v.end() - 1;

    while (low < high) {
        const auto sum = *low + *high;

        if (sum < total) {
            ++low;
        } else if (sum > total) {
            --high;
        } else if (*low == *high) {
            return res + (high - low) * (high - low + 1) / 2;
        } else {
            const auto prev_low = low;
            const auto prev_high = high;
            while (*prev_low == *low) {
                ++low;
            }
            while (*prev_high == *high) {
                --high;
            }
            res += (low - prev_low) * (prev_high - high);
        }
    }
    return res;
}

int main()
{
    std::cout << compute_box_combinaison({1, 2, 3, 5, 3}, 6) << std::endl; // 2 (1-5, 3-3)
    std::cout << compute_box_combinaison({1, 1, 1, 1, 1}, 2) << std::endl; // 10 (1-1 * 10)
    std::cout << compute_box_combinaison({1, 5, 3, 3, 3}, 6) << std::endl; // 4 (1-5, 3-3, 3-3, 3-3)
    std::cout << compute_box_combinaison({1, 3, 3}, 4) << std::endl;       // 2 (1-3, 1-3)

    return 0;
}
