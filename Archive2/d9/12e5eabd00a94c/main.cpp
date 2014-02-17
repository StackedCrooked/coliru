#include <iostream>
#include <fstream>

struct A { /* whatever */ };
struct B { /* whatever */ };

namespace detail_
{
    std::ostream& puta( std::ostream& stm, A, std::false_type )
    { return stm << "write to non-file: A{ /* ... */ }" ; }

    std::ostream& puta( std::ostream& stm, A, std::true_type )
    { return stm << "write to file: A{ /* ... */ }" ; }

    std::ostream& putb( std::ostream& stm, B, std::false_type )
    { return stm << "write to non-file: B{ /* ... */ }" ; }

    std::ostream& putb( std::ostream& stm, B, std::true_type )
    { return stm << "write to file: B{ /* ... */ }" ; }
}

std::ostream& operator<< ( std::ostream& stm, A a )
{
    auto p = dynamic_cast<std::filebuf*>(stm.rdbuf()) ;
    return p ? detail_::puta( stm , a, std::true_type{} ) :
                detail_::puta( stm , a, std::false_type{} ) ;
}

std::ostream& operator<< ( std::ostream& stm, B b )
{
    auto p = dynamic_cast<std::ofstream*>( std::addressof(stm) ) ;
    return p ? detail_::putb( stm , b, std::true_type{} ) :
                detail_::putb( stm , b, std::false_type{} ) ;
}

int main()
{
    A a ;
    B b ;

    {
        std::filebuf fbuf ;
        fbuf.open( "some_file.txt", std::ios::out ) ;
        std::ostream ostm(&fbuf) ;
        ostm << a << '\n' ; // the right overload is called
        ostm << b << '\n' ; // the wrong overload is called
    }

    std::cout << std::ifstream( "some_file.txt" ).rdbuf() ;
}
