#include <iostream>
#include <algorithm>
#include <vector>
 
int main() 
{
    std::vector<int> v{1, 2, 2, 2, 3, 3, 2, 2, 1,5,5};
    std::vector<int>::iterator last;
 
    last = std::unique(v.begin(), v.end()); // 1 2 3 2 1 3 2 2 1
                                            //           ^
    for (std::vector<int>::iterator it = v.begin(); it != last; ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";
}