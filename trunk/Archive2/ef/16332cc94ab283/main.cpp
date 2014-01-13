// returns number of characters placed into buffer
// excluding the terminating null character
// returns -1 if the buffer is not large enough
int to_string( long value, char* buffer, int bufsz )
{
    if( value < 0 && bufsz > 2 )
    {
        value = -value ;
        buffer[0] = '-' ;
        int n = to_string( value, buffer+1, bufsz-1 ) ;
        if( n != -1 ) return n+1 ;
    }

    else if( value < 10  && bufsz > 1 )
    {
        buffer[0] = value + '0' ;
        buffer[1] = 0 ;
        return 1 ;
    }

    else
    {
        int digit = value%10 ;
        int n = to_string( value/10, buffer, bufsz-1 ) ;
        if( n != -1 && bufsz > (n+1) )
        {
            buffer[n] = digit + '0' ;
            buffer[n+1] = 0 ;
            return n+1 ;
        }
    }

    buffer[0] = 0 ;
    return -1 ;
}

#include <iostream>

int main()
{
    int values[] = { -12345678, 1234, 0, -9999, 100 } ;
    char cstr[128] ;

    for( int v : values )
    {
        int n = to_string( v, cstr, sizeof(cstr) ) ;
        if( n>0 ) std::cout << cstr << " [" << n << "]\n" ;
    }
}
