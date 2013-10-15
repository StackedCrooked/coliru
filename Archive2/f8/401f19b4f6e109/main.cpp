#include <map>
#include <functional>
#include <set>
#include <string>
#include <iostream>

int main(int argc, char** argv) {
    // make a look up table that stores functions
    
    std::map<std::string, std::function<void(int, int)>> table;
    
    // add things to the table
    table["add"] = [](int x, int y) { std::cout << x + y << '\n'; };
    table["subtract"] = [](int x, int y) { std::cout << x - y << '\n'; };
    
    // check if the first argument is valid and in the look-up table
    if(argv[1] != nullptr && table.count(argv[1])) {
        // if it is, call the function
        table[argv[1]](std::stoi(argv[2]), std::stoi(argv[3]));
    }
    
    // of course with more error checking
} 