#include <iostream>
#include <cstdio>

using namespace std;

int main()
{
    string str = "0";
    printf("Str = %s \n", str.c_str());

    string strTemp = ""; //!= str
    
    sprintf((char*)strTemp.c_str(), "%d", 7); //ouch[0]
    printf("Str = %s\n" ,str.c_str());

    sprintf((char*)strTemp.c_str(), "%d", 8); //ouch[1]
    printf("Str = %s\n", str.c_str());

    return 0;
}