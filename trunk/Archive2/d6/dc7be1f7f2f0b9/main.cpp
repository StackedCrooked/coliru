#include <iostream>
#include <iomanip>

struct station
{
    std::string name;
    int student;
    int adult;
};


int main()
{
    int numStations = 4;
    station station[4] = { {"Spadina", 100, 200}, {"Bathurst", 100, 200}, { "Keele", 100, 200 }, { "Bay", 100, 200 } };
    std::cout << "Passes in Stock : Student Adult" << std::endl;
    std::cout << "-------------------------------" << std::endl;
    
    size_t headerWidths[3] = {
        std::string("Passes in Stock").size(),
        std::string("Student").size(),
        std::string("Adult").size()
    };
    
    
        for (int i = 0; i < numStations; i++) {
    
            std::cout << std::left << std::setw(headerWidths[0]) << station[i].name;
            std::cout << "   ";
            std::cout <<        std::setw(headerWidths[1]) << station[i].student 
                      << " " << std::setw(headerWidths[2]) << station[i].adult << std::endl;
    
        }
}
