#include <string>
using std::string ;

//turns binary back into decimal
int binToDec(string s)
{
    int value;
        if (s[0] = '1')
            value += 32;
        if (s[1] == '1')
            value += 16;
        if (s[2] == '1')
            value += 8;
        if (s[3] == '1')
            value += 4;
        if (s[4] == '1')
            value += 2;
        if (s[5] == '1')
            value += 1;

    return (value);
}
