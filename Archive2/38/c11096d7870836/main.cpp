#include <stdio.h>

int main()
{
    // ... prompt the 2 numbers
    
    puts( "MATH PRACTICE" );
    puts( "[+] addition" );
    puts( "[-] subraction" );
    puts( "[*] multiplication" );
    puts( "[/] division" );
    puts( "[x] EXIT\n" );
    printf( "Select : " );
    
    char operation;
    operation = getchar();
    
    switch( operation )
    {
    case '+' :
        // add the 2 numbers
        break;
    case '-' :
        // ...
        break;
    case '*':
        // ...
        break;
    case '/' :
        // ...
        break;
    case 'x' :
        break;
        
    default :
            ;
        // ...
    }
    
    return 0;
}