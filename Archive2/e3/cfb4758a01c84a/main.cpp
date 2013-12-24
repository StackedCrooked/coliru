#include <iostream>
#include <fstream>
#include <vector>

int main()
{
    const char txt_one[] = "file.text.1" ;
    const char binary[] = "file.binary" ;
    const char txt_two[] = "file.text.2" ;

    // create a text file containing literal integers seperatoed by space
    {
        std::ofstream file(txt_one) ;
        for( int i = 0 ; i < 10 ; ++i ) file << i*i*i << ' ' ;
        file << '\n' ;
    }
    std::cout << txt_one << " contains: " << std::ifstream(txt_one).rdbuf() ;

    // read the integers into a vector
    std::vector<int> seq ;
    {
        std::ifstream file(txt_one) ;
        int i ;
        while( file >> i ) seq.push_back(i) ;
    }
    std::cout << "the vector contains: " ;
    for( int v : seq ) std::cout << v << ' ' ;
    std::cout << '\n' ;

    // write the integers in the vector in binary form
    {
        std::ofstream file( binary, std::ios::binary ) ;
        for( int v : seq ) file.write( reinterpret_cast<const char*>(&v), sizeof(v) ) ;
    }

    // read integers from the binary file and write them into a text file
    // as literal integers seperatoed by space
    {
        std::ifstream infile( binary, std::ios::binary ) ;
        std::ofstream outfile(txt_two) ;
        int v ;
        while( infile.read( reinterpret_cast<char*>(&v), sizeof(v) ) )
              outfile << v << ' ' ;
        outfile << '\n' ;
    }
    std::cout << txt_two << " contains: " << std::ifstream(txt_two).rdbuf() ;
}
