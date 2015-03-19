#include <fstream>
#include <iostream>
#include <string>

class Grid
{
public:
    Grid(const std::string& path);
    
    bool is_good() {return !corrupt;}
    
    
private:
    bool load_file(std::string path);

    bool corrupt;
};

Grid::Grid(const std::string& path)
    : corrupt(false)
{ 
    //Open file
    std::fstream file;
    file.open("sudoku_1.txt");
    
    std::cout << '\n';
    
    char c;
    //Read file
    while (file >> std::noskipws >> c)
    {
        std::cout << c;
    }
    
    //Close file
    file.close();
}

int main()
{
    Grid("sudoku_1.txt");
    
    return 0;
}