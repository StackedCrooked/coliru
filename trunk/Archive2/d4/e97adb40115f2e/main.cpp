#include <string>
#include <iostream>

int main() {
    // brute force counting
    int count = 0;
    for ( int i = 1000; i < 9999; ++i ) {
        std::string istr = std::to_string( i );
        for ( std::size_t p = 0; p < 4; ++p ) {
            const char& c = istr[p];
            auto find = istr.find( c );
            if ( find == p )
                continue;
            if ( find != std::string::npos )
                ++count;
        }
    }
    std::cout << count << std::endl;
    return 0;
}