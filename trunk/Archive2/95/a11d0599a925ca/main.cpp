#include <string>
#include <fstream>
#include <iostream>

int main()
{
    const char file[] = "cube.obj";
    
    std::ifstream myfile;
    myfile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    
    try {
        myfile.open(file, std::ios::in);
        std::string line;
        while (std::getline(myfile, line))
        {
            // Foo
        }
    }
    catch(std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
}
