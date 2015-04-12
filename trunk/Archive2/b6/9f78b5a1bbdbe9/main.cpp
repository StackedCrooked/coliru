#include <algorithm>
#include <functional>
#include <array>
#include <iostream>
 
int main()
{
    std::array<int, 10> s = {5, 7, 4, 2, 8, 6, 1, 9, 0, 3}; 
 
    // sort using the default operator<
    std::sort(s.begin(), s.end());
    for (int a : s) {
        std::cout << a << " ";
    }   
    std::cout << '\n';
 
    // sort using a standard library compare function object
    std::sort(s.begin(), s.end(), std::greater<int>());
    for (int a : s) {
        std::cout << a << " ";
    }   
    std::cout << '\n';
 
    // sort using a custom function object
    struct {
        bool operator()(int a, int b)
        {   
            return a > b;
        }   
    } customLess;
    std::sort(s.begin(), s.end(), customLess);
    for (int a : s) {
        std::cout << a << " ";
    }   
    std::cout << '\n';
 
    // sort using a lambda expression 
    std::sort(s.begin(), s.end(), [](int a, int b) {
        return b < a;   
    });
    for (int a : s) {
        std::cout << a << " ";
    } 
    std::cout << '\n';
}