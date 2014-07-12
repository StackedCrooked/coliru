#include <iostream>
#include <vector>

struct colour{ char r, g, b, a; };

int main() {
    std::vector<char> input{ 1, 2, 3, 4, 4, 3, 2, 1 };
    
    auto casted = reinterpret_cast<colour*>(input.data());
    auto first = casted, last = casted + input.size() / 4;
    std::vector<colour> result(first, last);
            
    std::cout << result.size() << "\n";
    
    for (auto& e: result)
        std::cout << e.r << " " << e.g << " " << e.b << " " << e.a << "\n";
}