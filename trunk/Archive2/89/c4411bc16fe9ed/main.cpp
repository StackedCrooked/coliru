#include <iostream>
#include <fstream>

#define hello "hello"
#undef hello

int main()
{
    std::ifstream this_file( __FILE__ ) ; // open for input (std::ios::in)

    char my_char ;
    char directive[16] ;

    while( this_file.get(my_char) )
    {
        if( my_char == '#' ) //!!
        {
            std::cout << my_char ;

            this_file.read( directive, 7 ) ;
            directive[7] = 0 ; // null terminate

            std::cout << directive << '\n' ;
        }
    }
}
