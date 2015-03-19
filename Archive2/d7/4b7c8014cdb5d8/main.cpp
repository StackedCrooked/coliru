#include <fstream>
#include <iostream>
#include <string>

class Grid
{
public:
    //Init & Overloads
    Grid() {}
    
    //Status
    bool is_good() {return !corrupt;}
    
    //Utility
    bool load_file(const std::string& path);
    
private:
    
    //Private fields
    bool corrupt;
};

bool Grid::load_file (const std::string& path)
{
    //Open file
    std::fstream file;
    file.open("sudoku_1.txt");
    
    std::cout << '\n';
    
    char c;
    int i = 0;
    int j = 0;
    int buffer;
    
    bool row_flag = false;
    
    //Read file by character
    while (file >> std::noskipws >> c && i < 8)
    {
        //Keep going until you read {
        if (c != '{')
            continue;
        //If new row, flip flag
        else if (row_flag == false)
            row_flag = true;

            
        while(row_flag)
        {
            //Read a character
            file >> std::noskipws >> c;
            
            //Check if end of row
            if (c == '}')
            {
                //If row end early, bad
                if (j < 9)
                {
                    std::cout << "\nError: Grid row " << i + 1;
                    std::cout << " has less than 9 numbers" << std::endl;
                    corrupt = true;
                    break;
                }
                //Else set end of row
                else
                    row_flag = false;
            }
            
            //Check for "variable" or empty space
            if (c == 'X' || c == 'x' || c == '0')
            {
                std::cout << "x";
                buffer = -1;
                ++j;
            }
            //Convert to number
            else 
            {
                buffer = c - '0';
            
                //Check if 1-9
                if (buffer >= 1 && buffer <= 9)
                {
                    std::cout << buffer;
                    ++j;
                }
                //Discard all else
                else;
            }
            
            //If more than 9 numbers, bad
            if (j > 9)
            {
                std::cout << "\nError: Grid row " << i + 1 << " has more than 9 numbers";
                std::cout << " or is not closed with }" << std::endl;
                corrupt = true;
            }
            
            //If corrupt, stop reading file
            if (corrupt)
                break;
            
        }
        
        //Increment row
        std::cout << '\n';
        j = 0;
        ++i;
    }
    
    //Close file
    file.close();
    
    if (file.fail())
    {
        std::cout << "\nError: File I/O error. ( file.fail() )" << std::endl;
        corrupt = true;
    }
    
    return !corrupt;
}

int main()
{
    Grid grid;
    
    if (grid.load_file("sudoku_1.txt"))
        std::cout << "File loaded successfully." << std::endl;
    else
        std::cout << "File failed to load successfully." << std::endl;
        
    
    if (grid.is_good())
        std::cout << "Good!\n";
    else
        std::cout << "Bad!\n";
    
    return 0;
}

//sudoku_1.txt
/*

This sudoku grid
was created from the one at
http://en.wikipedia.org/wiki/Sudoku_solving_algorithms

{02X,45X,78X}
{4X6,7X9,1X3}
{78X,12X,45X}
-------------
{X34,X67,X91}
{5X7,8X1,2X4}
{89X,23X,56X}
-------------
{X45,X78,X12}
{6X8,9X2,3X5}
{91X,34X,67X}

------------------------
| Parser Specification |
------------------------

The program will ignore everything that is not {}, 0-9, and X or x.
You can use this to comment in files or even within the rows.
For example, I put commas to separate the rows and dashes for the box line.

The program won't read past 9 rows.

{ = Signifies that the row is beginning. More than 1 in a row will not give an error.
} = Row is ending. More than 1 in a row will not give an error.
1-9 = The number values. Stored in grid as is.
0, X, x = Placeholder or empty space. Will be stored as -1.

*/