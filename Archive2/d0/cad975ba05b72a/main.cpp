#include <iostream>
#include <string>
#include <iterator>
#include <sstream>
#include <limits>

std::stringstream istreams("Map: Out of planet\nPlayer:    Max");

int main()
{
    std::string killMap;

    istreams.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    if (!std::getline(istreams >> std::ws, killMap) || killMap.empty())
    {
        std::cerr << "There has been an error\n";
    }
    
    std::cout << killMap << '\n';
    
    istreams.ignore(std::numeric_limits<std::streamsize>::max(), ':');
    if (!std::getline(istreams >> std::ws, killMap) || killMap.empty())
    {
        std::cerr << "There has been an error\n";
    }
    
    std::cout << killMap << '\n';
}