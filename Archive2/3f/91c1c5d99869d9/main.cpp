#include <iostream>
#include <string>

int main( int argc, /*const char** argv*/ char* argv[] )
{
        if (argc < 3 )
        {
    usage:
            std::cerr << "Usage: " << argv[0] << " -e <text to encrypt>\n"
                      << "       " << argv[0] << " -d <text to decrypt>\n" ;
            return 1 ;
        }

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
            goto usage ;
        }
}
