#include <iostream>
#include <string>
#include <vector>
#include <cmath>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)

{
    double Ai, Aj, Ak, Bi, Bj, Bk, i, j , k, AxB, theta;
    std:: cout << "\n\t ingrese la componente i del vector A: " ;
    std:: cin >> Ai ;
    std:: cout << "\n\t ingrese la componente j del vector A:" ;
    std:: cin >> Aj ;
    std:: cout << "\n\t ingrese la componente k del vector A:";
    std:: cin >> Ak ;
    std:: cout << "\n\t ingrese la componente i delvector B:" ;
    std:: cin >> Bi;
    std:: cout <<  "\n\t igrese la compoente j del vector B:" ;
    std:: cin >> Bj ;
    std:: cout << "\n\t ingrese la ocmponente k del vector B:" ;
    std:: cin >> Bk ;
    i= Aj * Bk - Bj * Ak ;
    j= Ai * Bk - Bi * Ak ;
    k= Ai * Bj - Bi * Aj ;
    AxB = sqrt (pow ( Aj*Bk-Bj*Ak, 2) + pow ( Ai*Bk-Bi*Ak, 2) + pow ( Ai*Bj-Bi*Aj, 2)) ;
    theta= atan ( Aj+Bj ) / ( Ai+Bi ) ;
    std:: cout << "\n\t la componente rectangular i del producto vectorial AxB es:" << i << "su componente j es:" << j << " su componente k es: " << k << " la magnitud  del producto vectorial es " << AxB << "el angulo etre los vectores es: " << theta << "radianes" ;
    
    
    
    
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
}
