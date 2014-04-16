http://www.sgi.com/tech/stl/Predicate.html#include <vector>
#include <list>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <iostream>

template <class Container, class Function>
Function directional_for_each(Container& container, Function fn, bool reversed = false)
{
    return reversed
        ? std::for_each(container.rbegin(), container.rend(), fn)
        : std::for_each(container.begin(), container.end(), fn);
}

int main() {
    auto fn = [](int i) {
        std::cout << i << " ";
    };

    bool undoing = true; // true for reversed, false otherwise
    
    {
        std::vector<int> vec{ 1, 2, 3, 4, 5, 6, 7, 8 };
        directional_for_each(vec, fn, undoing);
        std::cout << "\n";
    }

    {
        std::list<int> lst{ 1, 2, 3, 4, 5, 6, 7, 8 };
        directional_for_each(lst, fn, undoing);
        std::cout << "\n";
    }

    {
        std::set<int> s{ 1, 2, 3, 4, 5, 6, 7, 8 };
        directional_for_each(s, fn, undoing);
        std::cout << "\n";
    }

    {
        std::map<int, int> m{ { 1, 2 }, { 3, 4 }, { 5, 6 }, { 7, 8 } };

        directional_for_each(m, [](std::pair<int, int> i) {
                std::cout << i.first << " " << i.second << std::endl; }, undoing);
    }
}
