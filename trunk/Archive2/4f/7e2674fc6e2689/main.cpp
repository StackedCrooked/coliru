#include <iostream>
#include <vector>
#include <functional>

int main() 
{
    int arr[] = {10, 20, 30};
    std::vector<std::reference_wrapper<int>> vec{arr[0], arr[1], arr[2]};
    
    vec.reserve(1000);
    
    for(auto const& v : vec) {
        std::cout << v << std::endl;
    }
}
