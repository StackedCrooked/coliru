#include <iostream>
#include <fstream>

void PrepareOBJ( std::ifstream& inputFile, std::ostream& out ) // replace result type with newline oid
{
    // copy contents of input file to output file, replacing 'v' (this one too) with '\n'
    char c ;
    while( inputFile.get(c) ) out << ( c == 'v' ? '\n' : c ) ; // (and one on this line too)
}

int main()
{ 
    std::ifstream this_file( __FILE__ ) ;
    PrepareOBJ( this_file, std::cout ) ;
    
    // abcdefgh v(replace with '\n') ijkl v(replace with '\n') ***
    // mnop v(replace with '\n') qrstu v(replace with '\n') wxyz ***
}
