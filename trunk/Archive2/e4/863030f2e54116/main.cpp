#include <algorithm>
#include <list>
#include <vector>
#include <iostream>
#include <functional>
 
int main()
{
    std::list<int> l = {-4, -3, -2, -1, 0, 1, 2, 3, 4};
 
    std::vector<std::reference_wrapper<int>> v(l.begin(), l.end());
    std::random_shuffle(v.begin(), v.end());
 
    std::cout << "Contents of the list: ";
    for (int n : l) {
        std::cout << n << ' ';
    }
    std::cout << '\n';
 
    std::cout << "Contents of the list, shuffled: ";
    for (int i : v) {
        std::cout << i << ' ';
    }
    std::cout << '\n';
 
    std::cout << "Doubling the values in the initial list...\n";
    for (int &i : l) {
        i *= 2;
    }
 
    std::cout << "Shuffled vector actually contains references: ";
    for (int i : v) {
        std::cout << i << ' ';
    }
    std::cout << '\n';
}