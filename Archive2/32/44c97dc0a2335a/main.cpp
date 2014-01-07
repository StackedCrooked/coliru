#include <iostream>
#include <fstream>
#include <cstdio>

int main()
{
    const char* const file_name = "swapped.txt" ;
    const char* const temp_file_name = "final_decrypted.txt" ;

    char RunAgain = 'y';

    while( (RunAgain=='y') || (RunAgain=='Y') )
    {
        char x ;
        std::cout << "Enter the character that you want to replace: " ;
        std::cin >> x;

        char y ;
        std::cout << "Enter the character that you want to replace it with: " ;
        std::cin >> y;

        {
            std::ifstream ifile(file_name) ; // open input file for reading
            std::ofstream ofile(temp_file_name) ; // open temp file for writing

            char c ;
            while( ifile.get(c) ) // for every character (including white space)  in ifile
                ofile.put( c == x ? y : c ) ; // write (replaced) character to ofile
        }

        // copy contents of temp file to the original file
        { std::ofstream(file_name) << std::ifstream(temp_file_name).rdbuf() ; }

        std::remove(temp_file_name) ; // delete the temp file

        std::cout << "Enter y to run this program again. Enter any other letter to quit: " ;
    	std::cin >> RunAgain;
    }

    // examine the contents of the modified file
    std::cout << std::ifstream(file_name).rdbuf() ;
}
