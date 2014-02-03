#include <iostream>
#include <sstream>
#include <utility>
#include <map>

std::stringstream in("1 3 2 5 4 7 9" " 9 8 5 1 4 2 7 ");
 
int main()
{
    std::map<std::pair<int, int>, int> pairToCount;
    int a, b;

    while (in >> a >> b)
    {
        auto it = pairToCount.find(std::make_pair(b, a));
        
        ++pairToCount[
            (it != pairToCount.end()) ? std::make_pair(b, a)
                                      : std::make_pair(a, b)];
    }
    
    for (const auto& p : pairToCount)
    {
        std::cout << "(" << p.first.first << " " << p.first.second << ") = "
                                                 << p.second << '\n';
    }
}