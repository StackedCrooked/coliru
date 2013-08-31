#include <deque>
#include <vector>
#include <iostream>
 
int main() 
{
    auto v = std::vector<int> { 0, 1, 2, 3 };
    auto d = std::vector<int*> { &v[0], &v[1], &v[2], &v[3] };
    
    for (auto ptr: d)
    {
        auto const i = std::distance(&d[0], &ptr);
        std::cout << *(d[i]) << "\n";
    }
}