#include <iostream>

int main() {
    double v1 = INT_MAX;
    double v2 = INT_MAX-1;
    if (v1==v2) 
        std::cout << "SAME";
    else
        std::cout << "DIFFERENT";
}