// http://stackoverflow.com/questions/28056551/how-to-convert-a-long-long-to-a-binary-character-string
// See also:
// http://stackoverflow.com/questions/15859649/why-is-data-sent-across-the-network-converted-to-network-byte-order

#include <iostream>
#include <cstdlib>
#include <string>
using std::string;

template< typename T >
void serial(T val, string & str, size_t N = sizeof(T)) {
    str[sizeof(T)-N] = char(val>>(8*(N-1)));
    if (--N) serial(val,str,N);
}

template< typename T >
string serialize( T val ) {
    string str( sizeof(T), 0 );
    serial( val, str );
    return str;
}

template< typename T >
T deserialize( const string & data, size_t N=sizeof(T)-1 ) {
    T top = N ? deserialize<T>(data,N-1) : 0;
    return (top << 8) | (unsigned char)(data[N]);
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
