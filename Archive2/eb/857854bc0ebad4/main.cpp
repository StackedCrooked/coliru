#include <iostream>
#include <string>
using namespace std;

int main()
{
    string c="chen";
	c[0]=c[1];
    c[1]=c[2];
    c[2]=c[3];
    cout<<c;
    return 0;
}
