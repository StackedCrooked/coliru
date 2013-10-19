#include <iostream>
#include <vector>

int main() {
    std::vector<bool> vector;
    vector.push_back(true);
    vector.push_back(false);
    
    for (const bool& i : vector)
        std::cout << i << "\n";

    return 0;
}