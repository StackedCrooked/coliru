#include <iostream>
#include <string>

using namespace std;

int main()
{
    wstring w(L"bla");
    string result;
    for(char x : w)
      result += x;
    
    cout << result << '\n';
}