#include <iostream>
#include <string>

//================ begin header file ============================
template< bool is_enabled = false > struct is_logger_enabled {
    static constexpr bool value = is_enabled;
};

struct Logger {
    template<bool enabled = false> void record( int argc, char const* argv[] );
};

template<> inline void Logger::record<false>( int argc, char const* argv[] ) {}
template<> inline void Logger::record<true>( int argc, char const* argv[] ) {
    std::cerr << "Logger: ";
    for(int i=0; i<argc; ++i) {
        std::cerr << " {" << i << ':' << argv[i] << '}';
    }
    std::cerr << std::endl;
}
//================ end header file ============================

// Specialization to enable logger, some place after include of header file
// ... but before Logger is instantiated
//
template<> struct is_logger_enabled<true>;

int main(int argc, const char* argv[])
{
    Logger log;

    std::cout << "Hello from GCC " << __VERSION__ << "!" << std::endl;

    log.record(argc,argv);
}
