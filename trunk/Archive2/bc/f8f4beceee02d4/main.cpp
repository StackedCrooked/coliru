#include <iostream>
#include <sstream>
#include <boost/date_time.hpp>

int main()
{
    boost::posix_time::ptime time;
    try 
    {
        std::stringstream ss("2014-12-19T15:53:14.533 MST-07");

        boost::local_time::local_time_input_facet* ifc= new boost::local_time::local_time_input_facet("%Y-%m-%d %H:%M:%S%F %ZP");
        //ifc->set_iso_extended_format();
        ss.imbue(std::locale(ss.getloc(), ifc));

        using namespace boost::local_time;
        local_date_time ldt(not_a_date_time);

        if(ss >> ldt) {
            time = ldt.utc_time();

            std::string remains;
            if (std::getline(ss, remains))
                std::cout << "Remaining: '" << remains << "'\n";
        }

    }
    catch( std::exception const& e )
    {
        std::cout << "ERROR:" << e.what() <<std::endl;
    }
    
    std::cout << "UTC time: " << time;
    
    return 0;  
}
