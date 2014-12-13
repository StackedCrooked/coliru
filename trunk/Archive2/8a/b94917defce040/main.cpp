#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

const int BYTE_STRING_LEN = 13;
typedef unsigned char byte;

struct bytestring
{
    bytestring(const byte* val)
    {
        memcpy(value, val, sizeof(value));
    }
    bytestring(const char* val)
    {
        memcpy(value, val, sizeof(value));
    }

    bool operator==(const bytestring& other) const
    {
        return memcmp(value, other.value, sizeof(value)) == 0;
    }

    byte value[BYTE_STRING_LEN];
};

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
    printNewSolution("hello there!!");
    printNewSolution("hello there!!");
}