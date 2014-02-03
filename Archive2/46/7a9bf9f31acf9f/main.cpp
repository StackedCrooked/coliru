#include <string>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
bool Existe(const string sChaine)
{
    return !sChaine.empty();
}

int CompterNombreCases(string sChaine[])
{
    return count_if(sChaine, * &sChaine, Existe);
}

 
int main()
{
    string str[] = {"dfafaf","fasafaf","sgsg","sg"};
    cout << CompterNombreCases(str);
    return 0;
}