#include <iostream>

int main()
    {
        std::cout << "Ratio entre 1.24, 2.6 et 0.2" << std::endl ;
        std::cout << "Ratio départ à 1" << std::endl;
        std::cout << "Ratio entre 1 et 1.24" << std::endl;
        std::cout << (1.24-1.0)/2.0+1.0 << std::endl; //On trouve le milieu entre 1 et 1.24
        std::cout << "Ratio entre 1.12 et 2.6" <<std::endl ; 
        std::cout << (2.6-1.12)/2.0+1.12 << std::endl;//On trouve le milieu entre 1.12 et 2.6
        std::cout << "Ratio entre 1.86 et 0.2 (donc ratio entre 1.24, 2.6 et 0.2)" << std::endl;
        std::cout << (0.2-1.86)/2+1.86 << std::endl;  //On trouve le milieu entre 1.86 et 0.2
    }
