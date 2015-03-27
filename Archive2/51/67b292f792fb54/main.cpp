#include <iostream>
#include <vector>

int main() {
    int x; // no default initialisation
    int y = int(); // assign from a default-constructed int
    std::vector<int> z(1); // as above, but in a vector
    
    std::cout << x << "\n";
    std::cout << y << "\n";
    std::cout << z[0] << "\n";
    
    return 0;
}