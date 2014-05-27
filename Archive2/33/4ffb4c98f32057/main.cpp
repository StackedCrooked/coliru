#include <iostream>
#include <cstring>
using namespace std;
 
int main()
{
    char str[10] = "123456789";
    const char *src = "abcdefghij";
    strcpy(str,src);
    cout << str << endl;
    return 0;
}