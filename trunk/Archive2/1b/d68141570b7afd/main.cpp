#include <cstdio>

struct A
{
    A& operator<< ( char c ) { std::printf( "%c", c ) ; return *this ; }
    A& operator<< ( int v ) { std::printf( "%d", v ) ; return *this ; }
    A& operator<< ( double d ) { std::printf( "%.2f", d ) ; return *this ; }
    A& operator<< ( const char* cstr ) { std::printf( "%s", cstr ) ; return *this ; }
};

int main()
{
    A cout ;

    A& r1 = cout.operator<< ( "the values are: " ) ;
    A& r2 = r1.operator<< (55) ;
    A& r3 = r2.operator<< ( " and " ) ;
    A& r4 = r3.operator<< (34.56) ;
    r4.operator<< ('\n') ;

    // using the references returned anonymously
    cout.operator<< ( "the values are: " ).operator<< (55).operator<< ( " and " ).
                       operator<< (34.56).operator<< ('\n') ;

    // or equvalently, using the operator:
    A& r5 = cout << "the values are: " ;
    A& r6 = r5 << 55 ;
    A& r7 = r6 << " and " ;
    A& r8 = r7 << 34.56  ;
    r8 << '\n' ;

    // using the references returned anonymously
    cout << "the values are: " << 55 << " and " << 34.56 << '\n' ;
}
