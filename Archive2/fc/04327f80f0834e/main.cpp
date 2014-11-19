#include <iostream>
#include <string>

int usage( const char* exe_name )
{
    std::cerr << "Usage: " << exe_name << " -e <text to encrypt>\n"
              << "       " << exe_name << " -d <text to decrypt>\n" ;
    return 1 ;
}

int main( int argc, char* argv[] )
{
        if (argc < 3 ) return usage( argv[0] ) ;

        const std::string option = argv[1];

        std::string text = argv[2];
        // cat the remaining cmd line args
        for( int i = 3 ; i < argc ; ++i ) { text += ' ' ; text += argv[i] ; }

        const std::string key("Passkey");

        if ( option== "-e" )
            std::cout << "Encrypt: '" << text << "'\n" ;

        else if ( option == "-d" )
            std::cout << "Decrypt: '" << text << "'\n" ;

        else
        {
            std::cout << "Unrecognised command line option '" << option << "'\n";
            return usage( argv[0] ) ;
        }
}
