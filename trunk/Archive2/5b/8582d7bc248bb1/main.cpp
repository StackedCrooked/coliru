#include <algorithm>
#include <iostream>
#include <cstdlib>
 
int main()
{
    std::vector<int> v(5);
    std::generate(v.begin(), v.end(), std::rand); // Используем C-функцию rand()
 
    std::cout << "v: ";
    for (auto iv: v) {
        std::cout << iv << " ";
    }
    std::cout << "\n";
}