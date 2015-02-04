#include <iostream>
#include <vector>
#include <string.h>

    struct debug_log_ignore {
      template <typename T>
      debug_log_ignore& operator<<(const T&) { return *this; }
      debug_log_ignore& operator<<(std::ostream& (*)(std::ostream&)) { return *this; }
    };

int main() {
    
    debug_log_ignore() << "works";
    
    debug_log_ignore() << " doesn't work " << std::endl;
    
    return 0;
}
