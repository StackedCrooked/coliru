#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
 
int main()
{
    std::vector<double> vecs[10] = std::vector<double>(10, 1);
    for(auto& vec: vecs ){
        std::copy(vec.begin(), vec.end(), std::ostream_iterator<double>(std::cout, " "));
        std::cout<<std::endl;
    }
    return 0;
}