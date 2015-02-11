#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <boost/format.hpp>

namespace logg {
    struct output {
        output() : device_(std::cout) {}
        std::ostream& device_;
    };

    template<typename T>
    output operator << (output trc, T&& t) {
        trc.device_ << std::forward<T>(t);
        return trc;
    }
    
    struct debug {
        debug(const std::string& fmt) : fmt_str_(fmt) {}        
        std::string fmt_str_;
    };
    
    template<typename T>
    std::string operator % (const debug& dbg, const T& t) {
        std::stringstream ss;
        ss << boost::format(dbg.fmt_str_) % t;
        return ss.str();
    }
}

#define log_output() if(!debug_level) (void)0; else logg::output()

std::string some_heavy_func() {
    std::cout << "in some heavy func\n";
    return "abcd";
}

int main() {
    int debug_level = 1;
    log_output() << logg::debug("this is log message: %1%") % some_heavy_func();
    
    debug_level = 0;
    log_output() << logg::debug("this is log message: %1%") % some_heavy_func();
}
