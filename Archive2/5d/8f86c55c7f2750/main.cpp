#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

int main()
{
    std::string filename;
    std::cin >> filename;
    
    std::ifstream file(filename);
    if (!file) {
        std::cout << "Can't open file, bailing out!";
        return 0;
    }
    
    std::string line;
    std::vector<int> v_ages;
    std::vector<std::string> v_names;
    
    int age;
    std::string name;
    char separator;
    
    while(getline(file, line)) {
        std::istringstream iss(line);
        iss >> name >> separator >> age;
        if (iss && separator == '=') {
            // add name and age to corresponding vectors
        } else {
            std::cout << "Line in wrong format, skipping.\n";
        }
    }
}