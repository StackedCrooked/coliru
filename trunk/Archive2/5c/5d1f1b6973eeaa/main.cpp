#include <iostream>

int main()
    {
        std::cout << "Ratio entre 1.24, 2.6 et 0.2" << std::endl << "=" << std::endl ;
        double ratioTotal {};
        ratioTotal = (1.24-1.0)/2.0+1.0; //Calculs de ratio
        ratioTotal = (2.6-1.12)/2.0+1.12;
        ratioTotal = (0.2-1.86)/2+1.86;
        std::cout << ratioTotal;
    }
