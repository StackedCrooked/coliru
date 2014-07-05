#include <iostream>

class Class
{
    public: Class( int i = 0 ) : m_i(i) {} 
    private: int m_i;
};

Class foo( Class object ) { return { 23 } ; }

int main()
{
    Class klass = { 1 };
    klass = foo( { 100 } ) ;
    std::cout << "ok\n" ;
}