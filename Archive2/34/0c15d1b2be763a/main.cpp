#include <iostream>
#include <fstream>
#include <utility>

int main()
{
    // at this point, std::cout shares a common buffer with std::printf

    std::ios_base::sync_with_stdio( false ) ; 
    // std::cout now has its own separate buffer. this buffer too, when flushed, 
    // writes the characters to the device associated with stdout 

    int i = 0 ;
    std::cout << ++i << ". this is written to stdout\n" ;

    std::cout << std::unitbuf ; // make std::cout flush the buffer after every output 
    std::cout << ++i << ". this too is written to stdout\n" ;

    // switch the buffer associated with std::cout to a file buffer
    std::filebuf fbuf ;
    fbuf.open( "temp.txt", std::ios::out );
    auto oldbuf = std::cout.rdbuf( std::addressof( fbuf ) ) ; 

    std::cout << ++i << ". this is written to the file\n" ;
    std::cout << std::nounitbuf ; // turn off unitbuf 
    std::cout << ++i << ". this too is written to the file\n" ;

    std::cout.rdbuf( oldbuf ); // restore std::cout's earlier buffer 
    std::cout << ++i << ". output is now back to stdout\n" << std::flush ;

    {
        // construct an ostream which shares the buffer with std::cout
        std::ostream my_stream( oldbuf ) ; 
        my_stream << ++i << ". this output too is to to stdout\n" << std::flush ;

        // my_stream and std::cout are 'synchronized'; write 'n. hello m. world' to stdout
        std::cout << ++i << ". hello " ;
        my_stream << ++i << ". world\n" ;
    }
}
