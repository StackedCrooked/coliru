#include <iostream>

int main()
{
    int i = 6 ;
    int j = 6 ;
    char jump = 'n' ;

    for(  ; i < 10 ; ++i )
    {
        if( i > 5 )
        {
            std::cout << "loop one begin \n" ;
            std::cout << "first part of loop one code\n" ;

            std::cout << "jump to loop two? " ;
            if( std::cin >> jump )
            {
                std::cout << "answer: '" << jump << "'\n" ;

                if( jump == 'y' || jump == 'Y' ) /* goto loop two */ { i = 0 ; j = 6 ; continue ; }
            }

            else return 0 ;

            std::cout << "second part of loop one code\n" ;
            std::cout << "loop one end \n" ;
        }

        else
        {
            for( ; j < 10 ; ++j )
            {
                if( j > 5 )
                {
                    std::cout << "loop two begin \n" ;
                    std::cout << "first part of loop two code\n" ;

                    std::cout << "jump to loop one? " ;
                    if( std::cin >> jump )
                    {
                        std::cout << "answer: '" << jump << "'\n" ;

                        if( jump == 'y' || jump == 'Y' ) /* goto loop one */ { j = 20 ; i = 6 ; continue ; }
                    }

                    else return 0 ;

                    std::cout << "second part of loop two code\n" ;
                    std::cout << "loop two end \n" ;
                }
            }
        }
    }
}
