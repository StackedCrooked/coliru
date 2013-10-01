#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector<int> vpn = {1, 1, 0, 0, 1, 0, 1}; // vec_prime_numbers
    int c = std::count(vpn.begin(), vpn.end(), 1);
    std::cout << c << "\n";
}
