#include <algorithm>
#include <vector>
#include <iterator>
#include <iostream>

void go(int depth, int s, int i, std::vector<int>& c, const std::vector<int>& v)
{
    if (depth == s)
    {
        do
        {
            std::copy(c.begin(), c.end(), std::ostream_iterator<int>(std::cout, " "));
            std::cout << "| ";
        }
        while (std::next_permutation(c.begin(), c.end()));
    }
    else
    {
        for (int j = i + 1; j < v.size(); ++j)
        {
            c.push_back(j);
            go(depth+1, s, j, c, v);
            c.pop_back();
        }
    }
}

int main()
{
    std::vector<int> v{ 0, 1, 2, 3 };
    std::sort(v.begin(), v.end());
    v.erase(std::unique(v.begin(), v.end()), v.end());    
    std::vector<int> c;
    go(0, 3, -1, c, v);
}
