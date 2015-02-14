#include <iostream>
#include <fstream>
#include <string>

int main()
{
    // read the same file twice: use two different stream objects
    {
        {
            std::ifstream file( __FILE__ ) ;
            int n = 0 ;
            char c ;
            while( file >> c ) ++n ;
            std::cout << n << " non-whitespace characters\n" ;

            // the life-time of the stream object is over; it is destroyed when the block is exited
        }

        {
            std::ifstream file( __FILE__ ) ; // create another stream object
            int n = 0 ;
            std::string str ;
            while( std::getline( file, str ) ) ++n ;
            std::cout << n << " lines\n" ;
        }
    }

    // read the same file twice: re-open the file
    {
        std::ifstream file( __FILE__ ) ;
        int nc = 0 ;
        char c ;
        while( file >> c ) ++nc ;
        std::cout << nc << " non-whitespace characters\n" ;

        // note: re-opening the file clears the failed state
        file.close() ;
        file.open( __FILE__ ) ;

        int ns = 0 ;
        std::string str ;
        while( std::getline( file, str ) ) ++ns ;
        std::cout << ns << " lines\n" ;
    }

    // read the same file twice: clear the failed state, seek to the beginning
    {
        std::ifstream file( __FILE__ ) ;
        int nc = 0 ;
        char c ;
        while( file >> c ) ++nc ;
        std::cout << nc << " non-whitespace characters\n" ;

        file.clear() ; // clear the failed state of the stream
        file.seekg(0) ; // seek to the first character in the file

        int ns = 0 ;
        std::string str ;
        while( std::getline( file, str ) ) ++ns ;
        std::cout << ns << " lines\n" ;
    }
}
