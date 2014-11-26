#include <vector>
#include <iostream>
#include <algorithm>
int main()
{
    std::vector<std::pair<int, int>> v = {{1,2}, {3,4}, {5,6}};
    auto p = std::make_pair(4, 4);

    if(std::find(v.begin(), v.end(), p) != v.end())
        std::cout << "yes\n";
}
