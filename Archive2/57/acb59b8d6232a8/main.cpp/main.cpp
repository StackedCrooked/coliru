//Author: !ixAlastor2
//referenced from: http://www.cplusplus.com/reference/regex/regex_search/
#include <iostream>
#include <string>
#include <regex>
using namespace std;
int main ()
{
  string A("stairs went downstairs do look up the stairwell");
  smatch mtch;
  regex e("\\b(stair)([^ ]*)");  
  cout << "String sequence: " << A << endl;
  
  while (regex_search (A,mtch,e)) {
    for (auto x:mtch) cout << x << " ";
    cout << endl;
    A = mtch.suffix().str();
  }

  return 0;
} 