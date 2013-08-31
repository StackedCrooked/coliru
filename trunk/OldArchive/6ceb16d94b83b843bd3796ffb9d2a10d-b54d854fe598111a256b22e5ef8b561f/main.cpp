#include <iostream>
#include <string>
#include <sstream>
 
int main()
{
    std::string str = "Daisy, Daisy, give me your answer, do,\nI'm half crazy all for the love of you.\nIt won't be a stylish marriage,\nI can't afford a carriage,\nBut you'd look sweet upon the seat\nOf a bicycle built for two. ";
    
    std::stringstream initialResults(str);
    std::string fileInMemory;
    initialResults.seekg(0, initialResults.end);
    
    fileInMemory.resize(initialResults.tellg());
    initialResults.seekg(0, initialResults.beg);
    initialResults.read(&fileInMemory[0], fileInMemory.size());
    
    
    std::cout << fileInMemory << "\n";
}