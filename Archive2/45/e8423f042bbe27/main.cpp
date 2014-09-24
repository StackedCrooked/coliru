#include <array>
#include <iostream>
 
int main()
{
    std::array<int*, 4> a {{new int(1), new int}};
    
    for (auto i : a) {
        std::cout << i << ' ';
    }
}
