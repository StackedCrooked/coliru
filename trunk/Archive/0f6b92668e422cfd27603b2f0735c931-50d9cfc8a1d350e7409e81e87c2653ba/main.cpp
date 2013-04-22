#include <iostream>
#include <vector> 
#include <algorithm>

auto nelio = [](int luku) { return luku * luku; };
auto kuutio = [](int luku) { return luku * luku * luku; };
auto tupla = [](int luku) { return luku * 2; };

int main()
{
    std::vector<int> luvut = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    for (auto i : luvut)
        std::cout << nelio(i) << " ";
    std::cout << std::endl;
    for (auto i : luvut)
        std::cout << kuutio(i) << " ";
    std::cout << std::endl;
    for (auto i : luvut)
        std::cout << tupla(i) << " ";
    std::cout << std::endl;
}

