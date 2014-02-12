#include <iostream>
#include <array>
#include <initializer_list>
 
template <class T, int N>
struct S {
    std::array<T, N> v;
    S(std::initializer_list<T> l) : v(l) {
         std::cout << "constructed with a " << l.size() << "-element list\n";
    }
};
 
int main()
{
    S<int, 5> s = {1, 2, 3, 4, 5}; // direct list-initialization
 
    for (auto n : s.v) std::cout << ' ' << n;
 
    std::cout << '\n';
 
    std::cout << "range-for over brace-init-list: \n";
 
    for (int x : {-1, -2, -3}) // the rule for auto makes this ranged for work
        std::cout << x << ' ';
    std::cout << '\n';
 
    auto al = {10, 11, 12};   // special rule for auto
 
    std::cout << "The list bound to auto has size() = " << al.size() << '\n';
}
