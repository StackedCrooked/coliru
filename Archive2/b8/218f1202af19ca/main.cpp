#include <iostream>
#include <string>
#include <vector>
#include <istream>

#include <ctype.h>

using std::cout;
using std::cin;

int main()
{
    char answer1;
 
    cout << "So, A, B, C or D?";
    answer1 = 'A';
    char lower = tolower(answer1);
    cout <<" You entered: " << lower << std::endl;

}
