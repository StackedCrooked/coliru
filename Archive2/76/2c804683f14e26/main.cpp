#include <stdio.h>

int main()
{
    char str[ 256 ];
    puts( "Enter your name: " );
    // kung scanf( "%s", str ); ang gagamitin, isang word lng ang
    // mariread.
    gets( str ); // get the whole line (sentence) instead
    
    printf( "Hello, %s !", str );

return 0;
}