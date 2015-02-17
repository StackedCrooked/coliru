#include <iostream>

int main()
{
    int i ;
    const int N = 10 ;

    ///////////////////////////////////////////////////////////////////////
    ////////////////////////// while ///////////////////////////////////
    ///////////////////////////////////////////////////////////////////////

        i = 0 ;

    loop_while:
        if( i < N )
        {
            // do these only if i < N
            std::cout << i << ' ' ;
            ++i ;
            goto loop_while ;

        }

        std::cout << '\n' ;

     ////////////////////////////////////

        i = 0 ;
        while( i < N )
        {
            // do these only if i < N
            std::cout << i << ' ' ;
            ++i ;
        }

        std::cout << '\n' ;

     ////////////////////////////////////

        i = 0 ;
        if( i < N )
        {
            // do these only if i < N
            do
            {
                std::cout << i << ' ' ;
                ++i ;
            } while( i < N ) ;
        }

        std::cout << '\n' ;

     ////////////////////////////////////

        for( i = 0 ; i < N ; ++i /* do this at the end, if i < N was true */ )
        {
            // do this only if i < N
            std::cout << i << ' ' ;
        }

        std::cout << '\n' ;




    ///////////////////////////////////////////////////////////////////////
    ////////////////////////// do while ///////////////////////////////////
    ///////////////////////////////////////////////////////////////////////

        i = 0 ;

    loop_do_while:

        // do these at least once, irrespective of whether, at the beginning,  i < N or not
        std::cout << i << ' ' ;
        ++i ;

        if( i < N )
        {
            goto loop_do_while ; // repeat loop if i < N
        }

        std::cout << '\n' ;

     ////////////////////////////////////

        i = 0 ;

        // do these at least once, irrespective of whether, at the beginning,  i < N or not
        std::cout << i << ' ' ;
        ++i ;

        while( i < N ) // repeat as long as i < N
        {
            std::cout << i << ' ' ;
            ++i ;
        }

        std::cout << '\n' ;

     ////////////////////////////////////

        i = 0 ;

        do
        {
            // do these at least once, irrespective of whether, at the beginning,  i < N or not
            std::cout << i << ' ' ;
            ++i ;
        } while( i < N ) ; // repeat as long as i < N

        std::cout << '\n' ;

     ////////////////////////////////////

        i = 0 ;

        // do these at least once, irrespective of whether, at the beginning,  i < N or not
        std::cout << i << ' ' ;
        ++i ;

        for( ; i < N ; ++i ) // repeat as long as i < N
        {
            std::cout << i << ' ' ;
        }
        std::cout << '\n' ;
}
