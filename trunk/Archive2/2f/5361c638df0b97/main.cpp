#include <iostream>
#include <complex>

class Class
{
    public: Class( int i = 0 ) : m_i(i) {} 
    private: int m_i;
};

Class foo( Class object, std::complex<double> c  ) { return { 23 } ; }

int main()
{
    Class klass = { 1 } ;
    Class klass2 { 56 } ;
    klass = foo( { 100 }, { 17, 4 } ) ;
    std::cout << "ok\n" ;
}