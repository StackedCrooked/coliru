//Author: !ixAlastor2
//referenced from: http://www.cplusplus.com/reference/regex/regex_search/
#include <iostream>
#include <string>
#include <regex>
using namespace std;
int main ()
{
  string A("alastairs went downstairs to look up the stairwell.");
  smatch mtch; 
  regex e ("([^ .\n]*)(stairs)([^ .\n]*)");  //<<<<<< you were right, it's not working
                                  //      I'm gonna install VS11 or code::blocks
  cout << "String sequence: " << A << endl;
  if (regex_search(A,mtch,e)) //////////Note: Try: regex_search(s,m,e)
  {
    cout << "string object matched\n";
    if (regex_match(A.begin(),A.end(),e))
    {
        cout << "range matched\n";
    }
    cmatch cm;    // same as std::match_results<const char*> cm;
  regex_match ("stairs went downstairs to look up the stairwell. stairs",cm,e);
  cout << "string literal with " << cm.size() << " matches\n";
    smatch sm;    // same as std::match_results<string::const_iterator> sm;
  regex_match (A,sm,e);
  cout << "string object with " << sm.size() << " matches\n";

  regex_match ( A.cbegin(), A.cend(), sm, e);
  cout << "range with " << sm.size() << " matches\n";
    regex_match ( "stairs went downstairs to look up the stairwell. stairs", cm, e, regex_constants::match_default );
    cout << "the matches were: ";
    for (unsigned i=0; i<sm.size(); ++i) {
        cout << "[" << sm[i] << "] ";
  }  }
  else
      cout << "no matches were made\n" << endl;
 
    //By the way, this is heavily outdated. I have one that actually works.
    //Kewl.
  while (regex_search(A,mtch,e))
  {
    for (auto x:mtch) cout << x << " ";
    cout << endl;
    A = mtch.suffix().str();
  }

  return 0;
}
