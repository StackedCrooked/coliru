#include <iostream>
#include <string>
#include <fstream>

int main()
{
    const char* const path = "file.txt" ;

    // create a test file
    {
        std::ofstream(path) << R"(Bailey           M CC 68
Harrison         F CC 71
Grant            M UN 75
Peterson         F UN 69
Hsu              M UN 79
Bowles           M CC 75
Anderson         F UN 64
Nguyen           F CC 68
Sharp            F CC 75
Jones            M UN 75
McMillan         F UN 80
Gabriel          F UN 62
)" ;
    }

    // echo input file
    {
        std::cout << std::ifstream(path).rdbuf() ;
    }

    // read data, and print out what was read
    {
        std::cout << "\n-----------\n" ;
        std::ifstream file(path) ;
        std::string name ;
        char sex ;
        std::string school ;
        int score ;

        while( file >> name >> sex >> school >> score )
        {
            std::cout << "name: " << name << '\n'
                      << "sex: " << sex << '\n'
                      << "school: " << school << '\n'
                      << "score: " << score << "\n\n" ;
        }
    }
}
