#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
using namespace std;

int main() {
    char s[100]="my country is very nice";
//	cin >> s;
	int len=0,w=1;
	while(s[len]!='\0')
	    len++;
	for(int i=0;i<len;i++)
	{
		if(s[i]==' ')
		    w++;
	}
	cout << " length is " << len << " and word is " << w << endl; 
	return 0;
}