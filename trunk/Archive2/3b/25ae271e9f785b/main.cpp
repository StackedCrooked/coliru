#include <string>

void foo( int i )
{
    label:
        {
            int j = i ;

            i -= j ;
        }

        if( i > 10 ) goto label ; // fine
}

void bar( int i )
{
        {
            int j = i ;
    label:
            i -= j ;
        }

        if( i > 10 ) goto label ; // *** error: jump bypasses variable initialization
}

void baz( int i )
{
        {
            std::string a ;
    label:
            --i ;
        }

        if( i > 10 ) goto label ; // *** error: jump bypasses variable initialization
}
