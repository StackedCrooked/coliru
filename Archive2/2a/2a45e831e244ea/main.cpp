#include <iostream>
#include <string>
#include <vector>
using namespace std;

//This does not work
//typedef string * string2d[2];
//typedef string *(&string2d)[2];

typedef string (&string2d)[23][2];

string2d flowFile() {
    static string flow[23][2];
   return flow;
}


int main()
{
    string s[23][2] = flowFile();
    s[0][0]="";
    return 0;
}
