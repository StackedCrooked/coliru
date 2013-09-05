#include <iostream>
#include <vector>
#include <numeric>
#include <string>
 
int multiply(int x, int y)
{
    return x*y;
}
 
std::string magic_function(std::string res, int x)
{
    return res += (x > 5) ? "b" : "s";
}
 
int main()
{
    std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
 
    int sum = std::accumulate(v.begin(), v.end(), 0);
    int product = std::accumulate(v.begin(), v.end(), 1, multiply);
    std::string magic = std::accumulate(v.begin(), v.end(), std::string(), 
                                        magic_function);
 
    std::cout << sum << '\n'
              << product << '\n'
              << magic << '\n';
}