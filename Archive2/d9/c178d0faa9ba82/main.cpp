#include <iostream>
#include <cstring>
#include <iomanip>
using namespace std;

char* concat(char *, char *);

int main()
{

char str1[20];
char str2[20];
char *x;
cout<< "Enter first word [str1]: ";
cin>> str1;
cout<< "Enter second word [str2]: ";
cin>> str2;

x = concat(str1, str2);
cout<< "New string value for [str1]: " << x << endl;
system("PAUSE"); 
}
char* concat(char * a, char * b)
{
char * result;
result = strcat(a, b);
return result;
}