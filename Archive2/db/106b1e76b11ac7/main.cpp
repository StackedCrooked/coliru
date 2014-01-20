#include <iostream>
#include <sstream>
#include <utility>
#include <map>

std::stringstream in("1 2 2 1 5 3 3 5");
 
int main()
{
    std::map<std::pair<int, int>, int> pairToCount;
    int a, b;

    while (in >> a >> b)
    {
        auto it = pairToCount.find(std::make_pair(b, a));
    
        if (it != pairToCount.end())
            pairToCount[std::make_pair(b, a)]++;
        else
        pairToCount[std::make_pair(a, b)]++;
    }
    
    for (const auto& p : pairToCount)
    {
        std::cout << "(" << p.first.first << " " << p.first.second << ") = "
                                                 << p.second << '\n';
    }
}