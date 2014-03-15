#include <iostream>

int main()
{
    const std::size_t N = 16 ;
    char hh[N], mm[N], ss[N] ;
    const char delimitador = ':' ;
    
    std::cout << "tiempo de entrada como hh:mm:ss\n" ; 
    std::cin.getline( hh, N, delimitador ) ; 
    std::cin.getline( mm, N, delimitador ) ; 
    std::cin.getline( ss, N ) ; // delimiter is '\n' 
    
    const int h = std::atoi(hh) ;
    const int m = std::atoi(mm) ;
    const int s = std::atoi(ss) ;
    
    std::cout << "Horas: " << h << "  Minutos: " << m << "  Segundos: " << s << '\n' ; 
}

