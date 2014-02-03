#include <iostream>
#include <cstring>

int counter = 0 ;
std::ostream& ccout() { return std::cout << ++counter << ". " ; }

struct A
{
    A( const char* cstr )
    {
        auto sz = cstr ? std::strlen(cstr) : 0 + 1 ;
        buff = new char[sz]{} ;
        if(cstr) std::strcpy( buff, cstr ) ;
        ccout() << "A{ \"" << buff << "\" } constructed\n" ;
    }

    ~A()
    {
        ccout() << "A{ \"" << buff << "\" } destroyed\n" ;
        std::memset( buff, ' ', std::strlen(buff) ) ;
        delete[] buff ;
    }

    A( const A& ) = delete ;
    A& operator= ( const A& ) = delete ;

    char* buff ;
};

void foo( const A& arg )
{
    ccout() << "foo::arg is alive at this point: " << arg.buff << '\n' ;
}

int main()
{
    char cstr[] = "abcd" ;

    const A& abcd = cstr ; // temporary object A{ "abcd" } constructed

    {
        const A& efgh = "efgh" ; // temporary object A{ "efgh" } constructed
        ccout() << "efgh is alive at this point: " << efgh.buff << '\n' ;

        foo( "ijkl" ) ; // temporary object A{ "ijkl" } constructed
        // end of full expression: anonymous temporary A{ "ijkl" } destroyed

    } // end of lifetime of reference efgh: anonymous temporary A{ "efgh" } destroyed

    const A& mnop = "mnop" ; // temporary object A{ "mnop" } constructed
    ccout() << "mnop is alive at this point: " << mnop.buff << '\n' ;
    ccout() << "abcd is still alive at this point: " << abcd.buff << '\n' ;

} // end of lifetime of reference mnop: anonymous temporary A{ "mnop" } destroyed
  // end of lifetime of reference abcd: anonymous temporary A{ "abcd" } destroyed
