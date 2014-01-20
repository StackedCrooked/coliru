#include <iostream>
#include <vector>

int main() {
    int i = 1, j = 2;
    int& ri = i;
    int& rj = j;
    std::swap( ri, rj );
    std::cout << i << ", " << j << '\n';
    std::cout << ri << ", " << rj << '\n';
}
