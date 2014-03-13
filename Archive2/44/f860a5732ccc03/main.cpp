#include <iostream>
#include <list>
#include <algorithm>
#include <iterator>
#include <set>
 
int main()
{
    std::list<int> l{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::multiset<int> s;
 
    std::fill_n(std::inserter(l, std::next(l.begin())), 3, -1);
    std::fill_n(std::inserter(s, s.begin()), 3, -1);
 
    for (int n : l) {
        std::cout << n << ' ';
    }
    std::cout << '\n';
 
    for (int n : s) {
        std::cout << n << ' ';
    }
    std::cout << '\n';
}