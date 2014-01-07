#include <cstddef>
#include <cstring>
#include <iostream>

int main( ) {
    
    struct small_integer_storage {
        union {
            int __res[16];
        } sso;
        int* __pres;
        
        small_integer_storage () {}
        
        small_integer_storage ( const int (& data)[16] ) {
            std::memcpy( sso.__res, data, sizeof( int ) * 16 );
            __pres = sso.__res;
        }
        
        small_integer_storage ( int* data ) {
            __pres = data;
        }
        
        small_integer_storage ( small_integer_storage&& mov ) : sso( mov.sso ) {
            if ( mov.__pres == mov.sso.__res )
                __pres = mov.sso.__res;
            else
                __pres = mov.__pres;
        }
        
        small_integer_storage& operator=( small_integer_storage&& mov ) {
            std::memcpy( &sso, &mov.sso, sizeof( sso ) );
            if ( mov.__pres == mov.sso.__res )
                __pres = mov.sso.__res;
            else
                __pres = mov.__pres;
            return *this;
        }
        
        int& operator[]( std::size_t idx ) {
            return __pres[idx];
        }
    };
    
    const int data[16] = { 1, 2, 3, 4, 5, 6, 7, 8 };
    small_integer_storage target;
    small_integer_storage move1( data );
    small_integer_storage move2( new int[ 1000 ]( ) );
    
    target = std::move( move2 );
    for ( std::size_t i = 0; i < 8; ++i ) {
        std::cout << target[i] << " ";
    }
    std::cout << '\n';

    target = std::move( move1 );
    for ( std::size_t i = 0; i < 8; ++i ) {
        std::cout << target[i] << " ";
    }
    std::cout << '\n';
    
}