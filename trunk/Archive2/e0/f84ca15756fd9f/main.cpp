#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> data{ 1, 2, 3, 4, 5, 4, 3, 2, 1 };
    std::vector<int> result;
    
    std::copy_if(data.begin(), data.end(), std::back_inserter(result),
        [done = false](int v) mutable{
            if (v >= 5) done = true;
            return !done;
        });
        
    for (auto& e: result)
        std::cout << e << " ";
}