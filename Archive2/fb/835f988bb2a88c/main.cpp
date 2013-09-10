#include <iostream>
#include <string>
#include <cmath>
#define Pi 3.14159265358979323846264338327950288419716939937510


int main(void)
{
    double b, A;
    std::cout << "n\tIngrese el valor del lado del cuadrado expresado en centimetros";
    std::cout <<"n\tb = ";
    std::cin >> b;
    A = 2*b*b*(Pi-2)/16;
    std::cout << "n\n\t El valor del area buscada es " << A << "centimetros cuadrados n\n\t";
    std::system("pause");
    return 0;
}
