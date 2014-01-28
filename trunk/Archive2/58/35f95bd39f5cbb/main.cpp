#include <string>
#include <cstring>
#include <iostream>

using namespace std;

int main()
{
  string s("test");
  cout << s.length() << '\n' << std::strlen(s.c_str()) << '\n';
}