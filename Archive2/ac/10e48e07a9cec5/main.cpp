#include <algorithm>
#include <iostream>
#include <vector>

struct MyOwnClass { int score; };

std::size_t get_index_of_nth_greatest(const std::vector<MyOwnClass>& v, std::size_t k)
{
    std::vector<std::size_t> indexes(v.size());
    std::iota(indexes.begin(), indexes.end(), 0);

    std::nth_element(indexes.begin(), indexes.begin() + k, indexes.end(),
        [&](int lhs, int rhs)
        {
            return v[lhs].score > v[rhs].score;
        }
    );
    return indexes[k];
}


int main()
{
    std::vector<MyOwnClass> scores = {{42}, {42}, {42}, {42}, {42}, {42}};

    for (std::size_t i = 0; i != scores.size(); ++i) {
        const auto index = get_index_of_nth_greatest(scores, i);
        std::cout << i << "th greater is at index " << index
            << " with value " << scores[index].score << std::endl;
    }
}
