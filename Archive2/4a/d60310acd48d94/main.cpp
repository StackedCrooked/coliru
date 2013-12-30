#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
 
int main()
{
    std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto inserter = std::back_inserter(v);
    inserter = 20;
    inserter = 30;
    inserter = 40;
    inserter = 50;
    for (int n : v)
        std::cout << n << ' ';
}