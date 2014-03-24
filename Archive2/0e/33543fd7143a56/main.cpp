#include <iostream>

using namespace std;

void cp(char *str2, char *str1){
    char *pom1 = str1;
    while(*pom1){
        pom1++;
    }
    char* pom2 = str2;
    while(*pom1 != *str1){
         pom1--;
        *pom2 = *pom1;
         pom2++;
    }
    *pom2 = '\0';
}

int main()
{
    char *str1 = "ppC", str2[10] = "Witaj";
    cout << "Napis str2 "<< str2 << endl;
    cp(str2,str1);
    cout << "Napis str2 "<< str2 << endl;
    cp(str2,"CJP");
    cout << "Napis str2 "<< str2 << endl;
    return 0;
}