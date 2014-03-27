#include <iostream>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/device/null.hpp>
#include <fstream>
#include <cassert>

void some_algorithm( std::ostream& log_file, const char* test_message )
{
    log_file << "test message: " << test_message << '\n' ;
    assert( log_file.good() ) ;
}

int main()
{
    std::ofstream logfile( "log.txt" ) ;

    using namespace boost::iostreams ;
    null_sink null ;
    stream<null_sink> null_ostream(null) ;

    some_algorithm( std::cout, "this is logged to stdout" ) ;

    some_algorithm( logfile, "this is logged to the file log.txt" ) ;

    some_algorithm( null_ostream, "this is not logged anywhere" ) ;
}
