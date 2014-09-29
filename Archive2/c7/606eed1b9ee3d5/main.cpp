#include <cstdlib>
#include <iostream>
#include <ctime>


int main() 
{
    std::srand(std::time(0)); // use current time as seed for random generator
    double x = (double) rand() / (RAND_MAX);
//    double y = ((double) rand() / (RAND_MAX));
    std::cout << "Random value on [0 " << RAND_MAX << "]: " 
              << x << '\n';
}