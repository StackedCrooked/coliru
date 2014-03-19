#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>
 
int main()
{
    std::vector<char> v = {'A','B','C'};
 
    std::random_device rd;
    std::mt19937 g(rd());
 
    std::shuffle(v.begin(), v.end(), g);
 
    copy(v.begin(), v.end(), std::ostream_iterator<char>(std::cout, " "));
    std::cout << "\n";
}