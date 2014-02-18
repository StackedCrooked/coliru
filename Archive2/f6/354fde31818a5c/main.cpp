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
  regex e ("(stair)(.*)");
  cout << "String sequence: " << A << endl;
  if (regex_match(A,e))
  {
    cout << "string object matched\n\n";
    if (regex_match(A.begin(),A.end(),e))
    {
        cout << "range matched\n";
    }
    cout << "The following matches were found: " << endl;
  }
  else
      cout << "no matches were made\n" << endl;
      
  while (regex_search(A,mtch,e))
  {
    for (auto x:mtch) cout << x << " ";
    cout << endl;
    A = mtch.suffix().str();
  }

  return 0;
}