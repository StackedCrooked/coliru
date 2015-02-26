#include <algorithm>
#include <string>
#include <iostream>
 
int main()
{
    std::vector<int> ints = {1,2,3,4};
    std::sort(ints.begin(), ints.end());
    auto pvec = [&]() {
        for (auto i: ints) std::cout << i << " ";        
    };
    do {
        pvec();
        std::cout << std::endl;
    } while(std::next_permutation(ints.begin(), ints.end()));
}