#include <iostream>
#include <algorithm>
#include <vector>



int main() {
    std::vector<int> a1, a2;

    a1 = {1,1,2,3,3,4,5,5,6};
    a2 = {1,2,3,4,5,6};
    
    std::vector<int> diff;
 
    std::set_difference(a1.begin(), a1.end(),
                          a2.begin(), a2.end(),
                          std::back_inserter(diff));
                          
    for(auto i : diff)
       std::cout << i << ' ';
                          
    return 0;
}