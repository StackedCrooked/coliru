#include <iostream>
#include <array>
#include <initializer_list>
 
template <class T>
struct S {
    std::array<T, 4> v;
    S(std::initializer_list<T> l) : v(std::array<T, 4>(l)) {
         std::cout << "constructed with a " << l.size() << "-element list\n";
    }
    
    std::pair<const T*, std::size_t> c_arr() const {
        return {&v[0], v.size()};  // list-initialization in return statement
                                   // this is NOT a use of std::initializer_list
    }
};
 
template <typename T>
void templated_fn(T) {}
 
int main()
{
    S<int> s = {1, 2, 3, 4, 5}; // direct list-initialization
 
    std::cout << "The vector size is now " << s.c_arr().second << " ints:\n";
 
    for (auto n : s.v) std::cout << ' ' << n;
 
    std::cout << '\n';
 
    std::cout << "range-for over brace-init-list: \n";
 
    for (int x : {-1, -2, -3}) // the rule for auto makes this ranged for work
        std::cout << x << ' ';
    std::cout << '\n';
 
    auto al = {10, 11, 12};   // special rule for auto
 
    std::cout << "The list bound to auto has size() = " << al.size() << '\n';
}