    #include "boost/date_time/posix_time/time_formatters_limited.hpp"
    #include <string>
    
    using namespace boost::posix_time;
    
    static inline std::string to_string(ptime p) {
        return boost::posix_time::to_simple_string(p);
    }
    
    int main()
    {
        ptime now = second_clock::local_time();
        std::cout << to_string(now) << std::endl;
    }