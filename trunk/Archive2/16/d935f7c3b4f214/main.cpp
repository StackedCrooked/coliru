#include <iostream>
#include <fstream>
#include <string>

struct A // base class, moveable, noncopyable
{
    virtual ~A() = default ;
    A() = default ; // file not opened
    A( std::string filename ) : log_file( filename, std::ios::app ) {}

    virtual bool open_log_file( std::string filename )
    {
        if( log_file.is_open() ) log_file.close() ;
        log_file.open( filename, std::ios::app ) ;
        return log_file.is_open() ;
    }

    virtual void test() { log_file << "from A: this is a test\n" ; }

    protected: std::ofstream log_file ;
};

struct B : A // derived class, moveable, noncopyable
{
    B() = default ; // file not opened
    B( std::string filename ) : A(filename) {}

    virtual void test() override
    {
        static int n = 0 ;
        log_file << ++n << ". from B (override): this is a test\n" ;
    }
};

int main()
{
    for( int i=0 ; i < 5 ; ++i )
    {
        B b( "1.txt" ) ;
        A& a = b ;

        a.test() ;
        a.A::test() ;
        
        a.open_log_file( "2.txt" ) ;
        a.test() ;
        b.A::test() ;
        
        a.open_log_file( "1.txt" ) ;
        a.test() ;
    }

    std::cout << "1.txt contains\n----------------\n" << std::ifstream( "1.txt" ).rdbuf() ;
    std::cout << "\n\n2.txt contains\n---------------\n" << std::ifstream( "2.txt" ).rdbuf() ;
}
