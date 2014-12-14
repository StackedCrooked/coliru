#include <iostream>
#include <sstream>

std::stringstream istreams("Map: something\nPlayer:    Max");

std::istream& eatwhites(std::istream& stream)
{
    while (stream && stream.peek() == ' ')
        stream.ignore();
    return stream;
}

int main()
{
    char characters[50];
    char killMap[50];
    if (!(istreams.getline(characters, 50, ':') >> eatwhites) || !istreams.get(killMap, 50) || !istreams.gcount())
    {
        std::cout << "Error!";
        return 0;
    }
    
    if (!(istreams.getline(characters, 50, ':') >> eatwhites) || !istreams.get(characters, 50) || !istreams.gcount())
    {
        std::cout << "Error!";
        return 0;
    }
    
    if (istreams && istreams.gcount())
        std::cout << killMap << '\n' << characters;
}