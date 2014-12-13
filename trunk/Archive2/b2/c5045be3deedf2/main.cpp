#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

typedef unsigned char byte;
typedef std::basic_string<byte> bytestring;

void printNewSolution(bytestring b)
{
    // check against known solutions to see if it's unique
    static std::vector<bytestring> KnownSolutions;
    if (std::find(KnownSolutions.begin(), KnownSolutions.end(), b) == KnownSolutions.end())
    {
        std::cout << "new" << std::endl;
        KnownSolutions.push_back(b);
    }
    else
        std::cout << "old" << std::endl;
}

int main()
{
    // Forcing 13 characters for this purpose.  I assume you have some way of reading these in.
    
    byte testBytes[] = "hello there!!";
    printNewSolution(testBytes);
    printNewSolution(testBytes);
}