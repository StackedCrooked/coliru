#include <utility>
#include <string>
#include <iostream>
#include <map>

using namespace std;

class X;
int main()
{
    std::map<int, char*> sMap = {{42, "meow"}{4711, "eau"}};
    int i;
    string s;
    for (tie(i,s) : sMap)
    {
      std::cout << i << "->" << s << '\n';
    }
}
