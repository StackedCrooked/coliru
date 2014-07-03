#include <iostream>
#include <map>

using namespace std; 
typedef pair<const string, const double> pr;
typedef map<const string,pr > mpr;
mpr mymap;
pr getvalue(const string s)
{
  pr pValue;
  mpr::iterator iter = mymap.find(s);
  if(1 /* Not quite sure what you meant here */)
  {
    pValue = (*iter).second;
  }
  return pValue;
}
int main( )
{
  getvalue("test");

}