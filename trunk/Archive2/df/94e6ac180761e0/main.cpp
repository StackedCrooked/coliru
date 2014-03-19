#include <iostream>
#include <sstream>
#include <locale>
#include <clocale>
#include <cwchar>
 
int main()
{
  const char* u8_string = u8"双喜雙喜!";
  
  std::mbstate_t state = std::mbstate_t();
  std::setlocale(LC_ALL, "en_US.utf8");
  int len = 1 + std::mbsrtowcs(NULL, &u8_string, 0, &state);
  std::wstring wstr(len, ' ');
  std::mbsrtowcs(&wstr[0], &u8_string, wstr.size(), &state);
  
  const wchar_t* LB_str = wstr.c_str();
  
  std::wcout.imbue(std::locale("en_US.utf8"));
  std::wcout << LB_str << '\n';
}