#include <iostream>
#include <string>

using namespace std;

int main()
{
    string s("Jochen");
    wstring result;
    for(char x : s)
      result += x;
    
    for(char  x : result)
      s += x;
    
    cout << s << '\n';
}