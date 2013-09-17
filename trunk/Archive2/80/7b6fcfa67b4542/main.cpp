#include <cstdlib>
#include <iostream>
#include <ctime>
#include <iterator>
#include <vector>
 
int main() 
{
    int rand_max = 100;
    std::srand(std::time(0)); // use current time as seed for random generator
    std::vector<int> testVector;
    for(int i = 0; i < 10;i++){
        testVector.emplace_back(std::rand() % rand_max);
    }
    std::copy(testVector.begin(), testVector.end(), std::ostream_iterator<int>(std::cout, " "));
}