#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

void compute(std::map<std::uint64_t, int>& counts, std::uint64_t i)
{
    std::vector<std::uint64_t> series;
    while (counts[i] == 0) {
        series.push_back(i);
        if ((i % 2) != 0) {
            i = (i * 3) + 1;
        } else {
            i /= 2;
        }
    }
    int count = counts[i];
    for (auto it = series.rbegin(); it != series.rend(); ++it)
    {
        counts[*it] = ++count;
    }
}

int main()
{
    const std::uint64_t limit = 1000000;

    std::map<std::uint64_t, int> counts;
    counts[1] = 1;
    for (std::size_t i = 2; i != limit; ++i) {
        compute(counts, i);
    }
    auto it = std::max_element(counts.begin(), counts.end(),
        [](const std::pair<std::uint64_t, int>& lhs, const std::pair<std::uint64_t, int>& rhs)
        {
            return lhs.second < rhs.second;
        });
    std::cout << it->first << ":" << it->second << std::endl;
    std::cout << limit-1 << ":" << counts[limit-1] << std::endl;
}
