#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <string>
 
int main()
{
    std::vector<std::pair<int, std::string>> v = { {2, "baz"},
                                                   {2, "bar"},
                                                   {1, "foo"} };
    std::sort(v.begin(), v.end());
 
    for(auto p: v) {
        std::cout << "(" << p.first << "," << p.second << ")\n";
    }
}