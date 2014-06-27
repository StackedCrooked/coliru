#include <iostream>
#include <string>
#include <vector>
#include <math.h>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

int main()
{
    int i;
    float stat2=1;
    float nbr2;
    for(i=0;i<4;i++){
        stat2 = stat2/pow(2,i+1);
        }
    nbr2 = 1/stat2;    
    
    std::cout << "Nombres d'animaux nessessaire pour les phases de poule : " << pow(3,48) << std::endl;
    std::cout << "Nombres d'animaux nessessaire pour avoir le gagnant de l'arbre ou de la petite finale (hors poule) : " << nbr2 << std::endl;
    std::cout << "Nombres d'animaux nessessaire pour avoir un sans faute (hors poule) : " << nbr2*2 << std::endl;
    std::cout << "Nombres d'animaux nessessaire pour avoir un sans faute (avec poule) : " << pow(3,48)*nbr2*2 << std::endl;
    
}
