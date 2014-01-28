#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

struct info
{
    static constexpr std::size_t name_size = 32 ;
    char name[name_size];
    int age;

    info() {}
    info( const char* n, int a ) : age(a) { std::strcpy( name, n ) ; }
};

int main()
{
    // create a test vector
    std::vector<info> test = { { "one", 1 }, { "two", 2 }, { "buckle", 100 },
                                { "my", 101 }, { "shoe", 102 }, { "three", 3 } };

    // print out its contents
    for( const info& inf : test )
        std::cout << "{ " << inf.name << ", " << inf.age << " } " ;
    std::cout << '\n' ;

    {
        std::ofstream file( "info.dat", std::ios::binary ) ; // output file stream

        // dump the contents of the vector in the file
        for( const info& inf : test )
            file.write( reinterpret_cast<const char*>( &inf ), sizeof(inf) ) ;
    } // the file is flushed and closed

    test.clear() ; // clear the vector

    {
        std::ifstream file( "info.dat", std::ios::binary ) ; // input file stream

        // read the contents of the file into the vector
        info inf ;
        while( file.read( reinterpret_cast<char*>( &inf ), sizeof(inf) ) )
            test.push_back(inf) ;
    } // the file is flushed and closed

    // print out the contents of test
    for( const info& inf : test )
        std::cout << "{ " << inf.name << ", " << inf.age << " } " ;
    std::cout << '\n' ;
}
