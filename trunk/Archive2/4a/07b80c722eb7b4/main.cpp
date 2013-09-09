#include <iostream>
#include <string>
#include <vector>
#include <cmath>
template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    double b; //lado del cuadrado
    const double pi = 3.1415926535; //contante pi
    double a;
std::cout << " \n\t Ingrese el lado del cuadrado en metros :";
std::cin >> b;
a=2*std::pow(b,2)*((pi/16)-(1/8));
std::cout<< " \n\t El area de la figura es: " << a << "metros cuadrados" <<"\n\t";

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
