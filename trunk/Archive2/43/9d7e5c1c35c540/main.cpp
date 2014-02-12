



        #include <fstream>

int main()
{
    std::ifstream file( __FILE__ ) ;

    char c ;
    if( file >> c ) file.putback(c) ;

    std::ofstream( "temp.txt" ) << file.rdbuf() ;

    // remove, rename
}
