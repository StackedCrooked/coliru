#include <iostream>
#include <fstream>
#include <memory>

int main()
{
    std::streambuf* stdout_buffer = std::cout.rdbuf() ; // the buffer that sends output to stdout
    std::filebuf fbuf ;
    fbuf.open( "/tmp/half_of_jabberwocky", std::ios::out ) ; // the buffer that sends output to a file
    std::streambuf* file_buffer = std::addressof(fbuf) ;
    
    const char* const jabberwocky[] = 
    {
        "’Twas brillig, and the slithy toves",
        "Did gyre and gimble in the wabe:",
        "All mimsy were the borogoves,",
        "And the mome raths outgrabe.",
        
        "“Beware the Jabberwock, my son!",
        "The jaws that bite, the claws that catch!",
        "Beware the Jubjub bird, and shun",
        "The frumious Bandersnatch!”",
        
        "He took his vorpal sword in hand;",
        "Long time the manxome foe he sought—",
        "So rested he by the Tumtum tree",
        "And stood awhile in thought."        
    };

    for( const char* line : jabberwocky )
    {
        static int n = 0 ;
        std::cout << ++n << ". " << line << '\n' ;
        std::cout.rdbuf( n%2 == 1 ? file_buffer : stdout_buffer ) ; // replace buffer
    }
    
    std::cout.rdbuf( stdout_buffer ) ; // restore original buffer
}
