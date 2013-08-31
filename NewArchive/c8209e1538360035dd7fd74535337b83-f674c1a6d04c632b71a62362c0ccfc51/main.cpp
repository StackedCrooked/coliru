#include <iostream>
#include <functional>
#include <mutex>

namespace you {
    class suck {
        unsigned long long big_balls;

        int j = 0;
        int meh(int i){return i++;}
        suck(){meh(j);}

    };
}


int main ( int argc, char* argv[] ) {
    const static std::size_t sz = sizeof( you::suck );
    
    std::cout << sz << std::endl;
    
}