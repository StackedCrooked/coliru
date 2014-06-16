#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <random>
#include <cmath>
int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());
 
    // values near the mean are the most likely
    // standard deviation affects the dispersion of generated values from the mean
    std::normal_distribution<double> d(0,1);

    for(int n=0; n<10; ++n) {
        std:: cout << d(gen) << std::endl;
    }
}