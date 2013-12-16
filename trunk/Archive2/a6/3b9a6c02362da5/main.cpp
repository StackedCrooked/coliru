#include <regex>
#include <iostream>

using namespace std;

int main()
{
   regex rgx("use_gui=((true|false)); state=((bla|blub|blob))");
   cmatch cm;
   string s("use_gui=false; state=bla");
   const bool ret = regex_match(s.c_str(), cm, rgx);

   std::cout << ret << '\n';
   for (auto x : cm)
      std::cout << x << '\n';
}