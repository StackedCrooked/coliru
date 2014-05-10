#include <map>
#include <vector>
#include <iostream>

template<class T>
std::map<T, int> count_series(const std::vector<T>& seq)
{
    std::map<T, int> series;
    if (!seq.empty())
    {
        auto current = seq[0];
        series[current] = 1;
        std::size_t i = 1;
        while (i < seq.size())
        {
            if (current != seq[i])
            {
                current = seq[i];
                series[current] += 1;
            }
        
            ++i;
        }
    }
    
    return series;
}

int main()
{
    std::vector<int> seq = {1,1,1,2,1,2,1,1,2,2,2,2,1,1};
    for (auto s : count_series(seq))
        std::cout << s.first << ": " << s.second << '\n';
}
