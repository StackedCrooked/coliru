    proposito: encintrar los puntosde interseccion entre dos rectas
    Entrada: Dos puntos que definen L1 y dos puntos que definan a L2
    salida:  Punto de interseccion de las recta L1 y L2
    Programadores: Marielos Lissette Perez Galdamez PG13054
               Karem Alejandra Hernandez Teos   HT13016
               Nataly Rocio Najarro Rios        NJ13015
    NOmbre del archivo: PRG1109. cpp
    Fecha; 10 de septiembre del 2013
    compilador:


#include <iostream>


    double x11, x12, x21, x22, y11, y12, y22, x,y ;


std::cout << " n\n\tIngrese las coordenadas de los puntos que definen a L1" ;
std::cout << " n\tx11= " ; 
std::cin >> x11 ;
std::cout << " n\ty11 ;
std::cin >> y11 ;
std::cout << " n\tx12= " ;
std::cin >> y12 ;
std::cout << " n\n\tIngrese las coordenadas de los puntos que definen a L2" ;
std::cout << "\n\tx21= " ;
std::cin >> x21 ;
std::cout << "\n\ty21= " ;
std::cin >> y21 ;
std::cout << "\n\tx22= " ;
std::cin >> x22 ;
std::cout << "\n\ty22= " ;
std::cin >> y22 ;

P1 = y11-y12/ x11-x12 ;

p2 = y22-y21/ x22-x21 ;

x= x11*p1-x21*p2+y21-y11/ p1-p2 ;

y=p1(x-x11)+y11 ;

std::cout << " n\tla abscisa del punto de inteseccion es ", << x << "y la ordenada de dicho punto es ", << y << ";


std:: system("pause")

    
    return os ;
{
   