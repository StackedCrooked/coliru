#include <iostream>
#include <string>
#include <vector>


int main()
{
  //http://stackoverflow.com/questions/15333259/c-stdwstring-to-stdstring-quick-and-dirty-conversion-for-use-as-key-in
  std::wstring ws(L"ABCD€FG");
  std::string s((const char*)&ws[0], sizeof(wchar_t)/sizeof(char)*ws.size());
  std::wstring nws((const wchar_t*)&s[0], sizeof(char)*s.size()/sizeof(wchar_t));
  std::cout << (1/2);
  std::cout << (nws==ws);
}
