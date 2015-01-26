#include <string>
#include <iostream>
#include <map>
#include <tuple>

using namespace std;

class X;
int main()
{
    map<int, string> myMap = {{42, "meow"}{4711, "eau"}};
    int i;
    string s;
    for (tie(i,s) : myMap)
    {
      cout << i << "->" << s << '\n';
    }
}
