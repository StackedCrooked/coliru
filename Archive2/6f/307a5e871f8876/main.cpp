#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector <unsigned short> wl = {1, 5, 7, 9};
    std::vector<unsigned short> sc = {2, 3, 7, 10};
    std::vector <unsigned short> temp;
    set_union(wl.begin(), wl.end(), sc.begin(), sc.end(), std::back_inserter(temp));
    wl = temp;
    std::cout << wl.size() << ' ' << std::endl;
    for (auto x : wl)
        std::cout << x << ' ';
    std::cout << std::endl;
}
