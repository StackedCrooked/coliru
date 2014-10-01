#include <iostream>
#include <sstream>
#include <vector>

struct temp_info // holds information in one line
{
    int day ;
    std::string local_time ;
    double dec_sol ;

    enum datum { ONE_M, POINT_FIVE_M, POINT_TWO_FIVE_M } ;
    double values[3] ;
};

temp_info to_temp_info( const std::string& line ) // retrieve  info from the line
{
     std::istringstream stm(line) ;
     temp_info ti ;
     if( stm >> ti.day >> ti.local_time >> ti.dec_sol )
     {
         for( double& v : ti.values ) stm >> v ;
         if(stm) return ti ;
     }
     return temp_info{} ; // value-initialised (day==0)
}

std::istream& skip_headers( std::istream& stm, int nlines = 4 )
{ while( nlines-- ) stm.ignore( 1000000, '\n' ) ; return stm ; }

// return selected day-temperature pairs
std::vector< std::pair<int,double> > read_filtered( std::istream& stm, int day, temp_info::datum col )
{
    skip_headers(stm) ;
    std::vector< std::pair<int,double> > result ;

    std::string line ;
    while( std::getline( stm, line ) )
    {
        auto ti = to_temp_info(line) ;
        if( ti.day == day ) // if this line has information about the day of interest
            result.emplace_back( ti.day, ti.values[col] ) ; // pick up the appropriate col. and add to result
    }

    return result ;
}

int main()
{
    std::istringstream file(
        R"(Mars temperature data
         ~ 24 hrs over two Solar days
        Sol Local T  Dec Sol Temperature (Celsius)
                                1.0m    0.5  0.25m
        2  11:59:08  2.486035  -25.4  -20.8  -17.4
        2  12:28:08  2.505635  -23.4  -18.8  -14.9
        3  04:44:02  3.191964  -75.0  -75.4  -77.7
        3  05:13:03  3.211575  -76.0  -76.4  -77.8
        3  05:42:04  3.231186  -74.7  -74.9  -75.9
        3  06:11:04  3.250786  -71.6  -71.7  -72.0
        3  02:47:59  3.113530  -71.9  -72.3  -73.9
        3  10:32:09  3.427243  -32.6  -28.8  -25.6
        3  11:01:09  3.446843  -29.8  -26.0  -22.4
        2  15:22:11  2.623269  -15.3  -12.7   -9.7
        2  15:51:12  2.642880  -18.9  -18.2  -15.1
        1  16:20:13  2.662490  -21.1  -20.9  -18.3
        5  19:14:18  2.780148  -45.7  -46.1  -46.9
        1  19:43:19  2.799760  -49.1  -49.4  -50.2
        2  20:12:20  2.819371  -51.5  -51.8  -52.7
        2  20:41:21  2.838982  -55.5  -55.8  -56.4
        4  23:06:26  2.937039  -64.9  -65.5  -66.9
        2  24:04:28  2.976262  -67.8  -68.5  -70.2
        3  00:51:55  3.035084  -69.3  -70.0  -71.1
        3  01:49:57  3.074307  -70.4  -70.7  -73.4
        4  02:18:58  3.093918  -71.3  -71.5  -73.2
        3  11:29:54  3.466274  -27.0  -23.5  -20.4
        3  12:27:55  3.505486  -22.3  -19.2  -15.7
        )"
    );

    for( auto pair : read_filtered( file, 2, temp_info::POINT_FIVE_M ) ) // day 2, temperature @0.5m
        std::cout << "measurement on day " << pair.first << "   temperature @0.5m is " << pair.second << '\n' ;
}
