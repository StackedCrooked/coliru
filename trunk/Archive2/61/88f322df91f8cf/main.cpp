#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <iomanip>

//This program is supposed to read in a Sudoku file of the format:
//{1,2,3,4,5}{29,38,15,..,5}...

//It ignores whitespace and all other characters.
//If you don't put a number, a {, a ',', or a } between the commas,
//It will register as an unknown (stored internally as 0).

//Try test it with this file:
//{1,2,3,}
//{X,X,2,1}
//{HELLO,WORLD,4,3}
//{@#,&%$,!@#,mmm}

int main() {

    std::fstream file;
    file.open("sudoku.txt");

    int x = 0;
    int y = 0;
    

    char c;
    std::string buffer;

    std::vector<int> row;
    std::vector<std::vector<int> > grid;

    bool row_flag = false;

    while(file >> std::noskipws >> c) {
        if (c == '{') {
            ++y;
            if (row_flag == true)
                break;
            else {
                row_flag = true;
            }
        } else if (c == ',' && row_flag) {
            row.push_back(std::atoi(buffer.c_str()));
            buffer.clear();
            ++x;
        } else if (c == '}' && row_flag) {
            row.push_back(std::atoi(buffer.c_str()));
            buffer.clear();
            ++x;
            row_flag = false;

            grid.push_back(row);
            
            row.clear();
            x = 0;
        } else if (c >= '0' && c <= '9' && row_flag) {
            buffer += c;
        } else {
            continue;
        }
    }

    if (row_flag == true) {
        std::cout << "ERROR: Unfinished row (missing })\n";
        return 1;
    }

    std::cout << "Row width: " << grid.at(0).size() << '\n';
    std::cout << "Row count: " << y << '\n';

    if (grid.at(0).size() != y) {
        std::cout << "ERROR: Sudoku table is of square dimensions.\n";
        return 3;
    }

    bool perfect_square = false;
    for (int i = 1; i <= grid.at(0).size()/2; ++i) {
        if (grid.at(0).size() == i*i)
            perfect_square = true;
    }

    if(!perfect_square) {
        std::cout << "ERROR: Sudoku dimensions are not a perfect square!\n";
        return 4;
    }


 
    try {
        for(int j = 0; j < grid.size(); ++j) {
            
            std::cout << "Row " << j+1 << ": { ";
            
            for (int i = 0; i < (grid.at(0)).size(); ++i) {
                if (grid.at(j).at(i) != 0)
                    std::cout << std::setw(3) << grid.at(j).at(i) << ' ';
                else
                    std::cout << "    ";
            }
            
            std::cout << "}\n"; 
        }
    } catch (...) {
        std::cout << "\nERROR: Sudoku rows are not of even size.\n";
        return 2;
    }

    return 0;
}
