#include <iostream>
#include <vector>
 
int main() 
{
    std::vector<int> v = {0, 1, 2, 3, 4, 5};
 
    for (const int &i : v) // access by const reference
        std::cout << i << ' ';
    std::cout << '\n';
 
    for (auto i : v) // access by value, the type of i is int
        std::cout << i << ' ';
    std::cout << '\n';
 
    for (auto&& i : v) // access by reference, the type of i is int&
        std::cout << i << ' ';
    std::cout << '\n';
 
    for(int n : {0,1,2,3,4,5}) // the initializer may be a braced-init-list
        std::cout << n << ' ';
    std::cout << '\n';
    
    struct range {
        int start; int stop;
        struct iter {
            int i;
            bool operator!=(iter other) { return other.i != i; };
            iter& operator++() { ++i; return *this; };
            int operator*() { return i; }
        };
        iter begin() { return iter{start}; }
        iter end() { return iter{stop}; }
    };
    for (auto n : range{0,6})
        std::cout << n << ' ';
    std::cout << '\n';
}