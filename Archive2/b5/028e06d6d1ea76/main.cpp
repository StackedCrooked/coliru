#include <iostream>
#include <string>
#include <vector>
#include <numeric>

int main()
{
    int i = 0;
    std::cin >> i;
    std::cout << i << std::endl;
    std::vector<int> v = {1,2,3,4,5,6};
    int sum = std::accumulate(v.begin(), v.end(), 0,
        [](int acc, int i) -> int {return i % 2 == 0 ? acc += i : acc;});
    std::cout << sum << std::endl;    
}
