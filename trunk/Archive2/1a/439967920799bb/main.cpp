#include <iostream>

#include <iostream>
#include <string>
#include <set>

using namespace std;

set<string> words = { "hello", "good", "morning" };

int main()
{
   for (auto w : words)
       cout << w << ' ';
}
