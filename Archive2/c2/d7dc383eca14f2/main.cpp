#include <iostream>
#include <algorithm>
#include <string>
#include <utility>
#include <vector>

int main()
{
    std::vector<float> counts = {1.2, 3.4, 5.6, 1.1, 7.8, 9.1, 2.3 };
    std::vector<std::pair<float, int>> value_idx;
    value_idx.reserve(counts.size());
    for (int i = 0; i < counts.size(); ++i) {
        value_idx.push_back(std::make_pair(counts[i], i));
    }
    
    // Get top n-th elems.
    for (int k = 0; k < 5; ++k) {
        auto top_k = value_idx.end() - 1 - k;
        std::nth_element(value_idx.begin(), top_k, value_idx.end());
        std::cout << "Top " << k << " : " << top_k->first
                  << " @ " << top_k->second << "\n";
    }
}
