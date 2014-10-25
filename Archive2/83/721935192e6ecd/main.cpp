#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

unsigned int countLines(std::ifstream in)
{
    std::string line;
    int lineCount = 0;
    while(getline(in, line))
        ++lineCount;
    return lineCount;
}

int main() {
    
}