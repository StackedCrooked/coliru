#include <iostream>
#include <sstream>
#include <locale>
#include <clocale>
#include <cwchar>
 
int main()
{
  const char* u8_string = u8"双喜雙喜!";
  
  wchar_t LB_str[100];
  std::setlocale(LC_ALL, "en_US.utf8");
  std::swprintf(LB_str, 99, L"%s", u8_string);
    
  std::wcout.imbue(std::locale("en_US.utf8"));
  std::wcout << LB_str << '\n';
}