#include <memory>
#include <unordered_map>
#include <iostream>

int main()
{
    std::unordered_map<int, std::unique_ptr<int>> m;
    
    m[0] = std::unique_ptr<int>(new int(10));
    m[1] = std::unique_ptr<int>(new int(20));
    
    auto it = m.find(1);
    if(it != m.end()) {
        std::cout << *(it->second) << '\n';
    }
}
