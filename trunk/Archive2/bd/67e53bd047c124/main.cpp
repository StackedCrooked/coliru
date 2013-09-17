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
 
    std::vector<std::reference_wrapper<int>> v2(v.begin(), v.end());
    std::partition(v2.begin(), v2.end(), [](int &n){return n<0;});
 
    std::cout << "Contents of the list: ";
    for(int n: l) {
        std::cout << n << ' ';
    }
    std::cout << '\n';
 
    std::cout << "Contents of the list, shuffled: ";
    for(int i: v) {
        std::cout << i << ' ';
    }
    std::cout << '\n';
 
    std::cout << "Shuffled elements, partitioned: ";
    for(int i: v2) {
        std::cout << i << ' ';
    }
    std::cout << '\n';
}