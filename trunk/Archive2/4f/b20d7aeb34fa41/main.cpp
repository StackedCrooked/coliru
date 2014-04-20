#include <iostream>
#include <string>
using namespace std;

int main()
{
char c[]="-13";
int num;
int i=0;
int sign = 1;
if (c[0]=='-') {
    sign = -1;
    i++;
}
 for (;c[i] != '\0'; ++i)
        num = num*10 + c[i] - '0';
cout << num*sign << endl;
string str = "Adott egy N szobol allo mondat";
string sent[6]; // 6 szavas mondatra
int g=0;
double len=0.0;
for (int j = 0; j<=str.size(); ++j) {

if (str [j]==' ' || j==str.size()) {
    len+=sent[g].size();
    g++;
}
else {
sent[g] = sent[g]+str[j];
}
}
cout << len/g << endl;
return 0 ;
}