#include <iostream>
#include <fstream>
#include <string>

class PwdReader_1
{
    public: explicit PwdReader_1( std::istream& i ) : in(i) 
            { std::string test ; std::getline(in,test) ; std::cout << test << '\n' ; }

    private: std::istream& in ;
};

#ifndef USING_BROKEN_GNU_LIBRARY
    class PwdReader_2
    {
        public: explicit PwdReader_2( std::ifstream&& i ) : in( std::move(i) ) 
                { std::string test ; std::getline(in,test) ; std::cout << test << '\n' ; }
    
        private: std::ifstream in ;
    };
#endif // USING_BROKEN_GNU_LIBRARY

class PwdReader_3
{
    public: explicit PwdReader_3( std::streambuf* buf ) : in(buf) 
            { std::string test ; std::getline(in,test) ; std::cout << test << '\n' ; }

    private: std::istream in ;
};

int main()
{
    {
        std::ifstream file( __FILE__ ) ;
        PwdReader_1 reader(file) ;
        // use reader
    }

    #ifndef USING_BROKEN_GNU_LIBRARY
    {
        PwdReader_2 reader( std::ifstream( __FILE__ ) ) ;
        // use reader
    }
    #endif // USING_BROKEN_GNU_LIBRARY

    {
        std::filebuf buf ;
        buf.open( __FILE__, std::ios::in ) ;
        PwdReader_3( std::addressof(buf) ) ;
        // use reader
    }
}
