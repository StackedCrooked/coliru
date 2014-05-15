#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int main()
{
   vector<string> w = { "one", "two", "two", "three", "one" };
   map <string, int> words;

   for (const auto &i : w)
      words[i]++;
   
   for (const auto &i : words)
      cout << i.first << " : " << i.second << endl;

   return 0;
}