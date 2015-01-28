#include <iostream>
#include <sstream>
#include <boost/date_time.hpp>

int main()
{
    boost::posix_time::ptime time;
    try 
    {
        std::stringstream ss("2014-12-19T15:53:14.533+01:00");
        boost::local_time::local_time_input_facet* ifc= new boost::local_time::local_time_input_facet();
        ifc->set_iso_extended_format();
        ss.imbue(std::locale(ss.getloc(), ifc));
        boost::local_time::local_date_time zonetime(boost::local_time::not_a_date_time);
        if( ss >> zonetime ) {
            time = zonetime.utc_time();
        }
    }
    catch( std::exception const& e )
    {
        std::cout << "ERROR:" << e.what() <<std::endl;
    }
    
    std::cout << "UTC time: " << time;
    
    return 0;  
}
