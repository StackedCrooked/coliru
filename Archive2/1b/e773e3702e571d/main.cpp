#include <iostream>
#include <string>

// Generic templated class to enable/disable functionality
//
template< typename T > struct is_enabled { using type = std::false_type; };

// Specialization to enable logger, before logger header file is included
//
struct Logger;
// Comment out following line to disable logger
template <> struct is_enabled < Logger > { using type = std::true_type; };


//================ begin header file ============================

struct Logger {
    
    void record_impl( int argc, char const* argv[], std::false_type )
    {} // do nothing
    
    void record_impl( int argc, char const* argv[], std::true_type ) {
        std::cerr << "Logger: ";
        for(int i=0; i<argc; ++i) {
            std::cerr << " {" << i << ':' << argv[i] << '}';
        }
        std::cerr << std::endl;
    }
    
    // http://www.generic-programming.org/languages/cpp/techniques.php#tag_dispatching
    //
    void record( int argc, char const* argv[] ) {
        record_impl( argc, argv, is_enabled<Logger>::type() );
    }
};

//================ end header file ============================

int main(int argc, const char* argv[])
{
    Logger log;

    std::cout << "Hello from GCC " << __VERSION__ << "!" << std::endl;

    log.record(argc,argv);
}
