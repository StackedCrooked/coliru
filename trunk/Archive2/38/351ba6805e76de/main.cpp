#include <iostream>
#include <cmath>
#include <iomanip>

int main()
{
    const double min_value = 3.0e-10 ;
    const double max_value = 5.0e+10 ;

    const double min_log = std::log(min_value) ;
    const double max_log = std::log(max_value) ;

    const int num_intervals = 10 ;
    const double log_increment = ( max_log - min_log ) / num_intervals ;

    double value = min_value ;
    double log_value = min_log ;
    std::cout << std::scientific << std::setprecision(5) << "intervals\n--------\n" ;
    for( int i = 0 ; i < num_intervals ; ++i )
    {
        std::cout << std::setw(2) << i+1 << ". " << value  << " - " ;
        log_value += log_increment ;
        value = std::exp(log_value) ;
        std::cout << value << '\n' ;
    }
}
