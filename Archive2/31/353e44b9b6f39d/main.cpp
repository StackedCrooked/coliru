#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <ctime>


int main()
{
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
 
    std::srand(unsigned(std::time(0)));
 
    std::random_shuffle(v.begin(), v.end());
 
    std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";
}