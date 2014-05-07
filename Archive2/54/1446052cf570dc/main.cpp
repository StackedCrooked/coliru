#include <iostream>
#include <fstream>

int main()
{
    std::ofstream file("banana.txt");
    const int i = 42;
    
    file << i;
    
    return 0;
}