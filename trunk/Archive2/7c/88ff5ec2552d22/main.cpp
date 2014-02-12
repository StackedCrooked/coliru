#include <vector>
#include <string>
#include <string.h>
#include <algorithm>
#include <iostream>

using namespace std;

class toto
{
  char v[10];

public:
  toto(char* t) { memcpy(v, t, 9); }
  bool test(const char* var) const { return !strncmp(var, v, 9); }
  bool test(const string& var) const { return test(var.c_str()); }
};

int main()
{
  vector<toto> t;
  t.push_back("1");
  t.push_back("2");
  std::cout << t.size() << "\n";
  string name("2");
  vector<toto>::iterator it = remove_if(t.begin(), t.end(),
       bind2nd(mem_fun_ref((bool (toto::*)(const string&) const) &toto::test), name));
  t.erase(it, t.end());
  std::cout << t.size();
  return 0;
}