// http://stackoverflow.com/questions/28056551/how-to-convert-a-long-long-to-a-binary-character-string
// See also:
// http://stackoverflow.com/questions/15859649/why-is-data-sent-across-the-network-converted-to-network-byte-order

#include <iostream>
#include <cstdlib>
#include <string>
using std::string;

template< typename T >
string serialize( T val ) {
    string str( sizeof(T), 0 );
    for(size_t i=0; i<sizeof(T); ++i, val >>= 8)
        str[sizeof(T)-i-1] = char(val);
    return str;
}

template< typename T >
T deserialize( const string & data ) {
    T val = 0;
    for(size_t i=0; i<sizeof(T); ++i)
        val = (val << 8) | (unsigned char)data[i];
    return val;
}

int main(int argc, const char * argv[]) {
    
    for(int i=1; i<argc; ++i) {
        char *end;
        long long val = strtoll(argv[i], &end, 10);
        std::cout << " deserialize<long long>( serialize(" << val << ") ) = "
            << deserialize<long long>(serialize(val))
            << std::endl;
    }
}
