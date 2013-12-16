#include <iostream>
#include <string>
#include <vector>
#include <cstring>

struct int_int24_t { 
private: 
    int32_t foo:24; 
public: 
    operator int32_t() { return foo; } 
    int_int24_t & operator=(int32_t v) { /* check if fits */ foo = v; return *this; }
};

struct char_int24_t { 
private: 
    char foo[3]; 
public: 
    operator int32_t() { 
        int32_t v; 
        std::memcpy( &v, &foo, 3 ); 
        return v; 
    }
    
    char_int24_t& operator=(int32_t v) { 
        /* check if fits */ 
        std::memcpy( &foo, &v, 3 ); 
        return *this; 
    }
};

int main()
{
    std::cout << sizeof( char_int24_t ) << std::endl;
    std::cout << sizeof( int_int24_t ) << std::endl;
}
