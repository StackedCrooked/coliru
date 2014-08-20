#include <iostream>
#include <set>

int main()
{
    std::set<int, std::greater<int>> v { 3, 1, 4, 1, 5, 9 };

    std::cout << "initially, v: ";
    for (auto i : v) std::cout << i << ' ';
    std::cout << '\n';

    auto largest = *v.begin();
    v.erase(v.begin());
    std::cout << "largest element: " << largest << '\n';

    std::cout << "after removing the largest element, v: ";
    for (auto i : v) std::cout << i << ' ';
    std::cout << '\n';
}