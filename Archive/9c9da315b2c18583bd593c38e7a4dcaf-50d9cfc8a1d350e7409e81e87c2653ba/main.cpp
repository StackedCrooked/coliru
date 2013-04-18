#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>


using Sentence = std::vector<std::string>;


int square(int x)
{
    return std::pow(x, 2);
}


int main()
{
    std::vector<int> vect(10,0);
    std::vector<int> v2(10);
    
    std::transform(vect.begin(), vect.end(), v2.begin(), square);
    
    return 0;
}
