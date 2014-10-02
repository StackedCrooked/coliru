#include <iostream>
#include <iomanip>

int main()
{
    {
        std::cout << "experiment: what happens when a small number is added to a big number?"
                     "\n=======================================================================\n" ;
        double d = 1.0e12 ;
        const double e = 0.01 ;

        std::cout << std::fixed << std::setprecision(20) ;
        const auto w50 = std::setw(50) ;

        for( int i = 0 ; i < 8 ; ++i, d*=10 )
        {
            std::cout << w50 << d << " +\n" << w50 << e
                      << "\n---------------------------------------------------------\n"
                      << w50 << d+e << "\n\n" ;

            d *= 10 ;
        }

        std::cout << '\n' ;
    }


    {
        std::cout << "\nexperiment: what happens when a big number is subtracted from a small number?"
                     "\n=======================================================================\n" ;
        double d = 1.0e12 ;
        const double e = 0.01 ;

        std::cout << std::fixed << std::setprecision(20) ;
        const auto w50 = std::setw(50) ;

        for( int i = 0 ; i < 8 ; ++i, d*=10 )
        {
            std::cout << w50 << e << " -\n" << w50 << d
                      << "\n-----------------------------------------------------------------\n"
                      << w50 << e-d << "\n\n" ;

            d *= 10 ;
        }

        std::cout << '\n' ;
    }

    {
        std::cout << "\nexperiment: what happens when a big number is incremented?"
                     "\n=======================================================================\n" ;
        double d = 1.0e16 ;

        std::cout << std::fixed << std::setprecision(20) ;
        const auto w50 = std::setw(50) ;

        for( int i = 0 ; i < 8 ; ++i )
        {
            const double e = i+1 ;
            std::cout << w50 << d << " +\n" << w50 << e
                      << "\n-----------------------------------------------------------------\n"
                      << w50 << d+e << "\n\n" ;

        }

        std::cout << '\n' ;
    }
}
