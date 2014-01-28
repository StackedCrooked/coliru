#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>
 
int main()
{
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10,11 ,12 ,13,14,15,16,17,18,19,20};
 
    std::random_device rd;
    std::mt19937 g(rd());
 
    std::shuffle(v.begin(), v.end(), g);
 
    copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";
}