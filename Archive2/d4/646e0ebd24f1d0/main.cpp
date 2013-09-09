#include <iostream>
#include <string>
#include <vector>
#include <cmath>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    double x11;//coordenada en el eje "x" del punto p11 para la recta l1
    double y11;//coordenada en el eje "y" del punto p11 para la recta l1
    double x12;//coordenada en el eje "x" del punto p12 para la recta l1
    double y12;//coordenada en el eje "y" del punto p12 para la recta l1
    double x21;//coordenada en el eje "x" del punto p21 para la recta l2
    double y21;//coordenada en el eje "y" del punto p21 para la recta l2
    double x22;//coordenada en el eje "x" del punto p22 para la recta l2
    double y22;//coordenada en el eje "y" del punto p22 para la recta l2
    double m1;//pendiente de la recta l1
    double m2;//pendiente de la recta l2
    double x;//coordenadas del eje x del punto de interseccion de ambas rectas
    double y;//coordenadas del eje y del punto de interseccion de ambas rectas
    std::cout<<"\n\t ingrese las coordenadas del punto p11 parta la recta l1, \n\t a continuacion ingrese la coordenada x11:";
    std::cin >> x11;
     std::cout << "\n\t Ingrese la coordenada y11 :";
     std::cin >> y11;
      std::cout <<  "\n\t Ingrese las coordenadas del punto P12 para la recta L1,\n\t Acontinuacion ingrese la coordenada x12 : "; 
      std::cin >> x12;
      std::cout << "\n\t Ingrese la coordenada y12 :" ;
      std::cin >> y12;
      std::cout << " \n\t Ingrese las coordenadas del punto P21 para la recta L2,\n\tAcontinuacion ingrese la coordenada x21: " ;
      std::cin >> x21;
      std::cout << " \n\t Ingrese la coordenada y21 : " ;
       std::cin >> y21;
       std::cout << " \n\t Ingrese las coordenadas del punto P22 para la recta L1, \n\t Ingrese acontinuacion la coordenada en x22: " ;
        std::cin >> x22;
         std::cout << "\n\t Ingrese la coordenada en y22: ";
           std::cin >>y22;
           m1= ((x12-x11)/(y12-y11));
           m2=((x22-x21)/(y22-y21));
           x=(m1*x11-m2*x21-y11+y21)/m1-m2;
           y=(m1*x)-m1*x11+y11;
           std::cout << "\n\t las rectas se intersectan en el punto: X = " <<x << "\n\t y=" <<y <<" \n\n\t\t " ;
           system("pause");


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
