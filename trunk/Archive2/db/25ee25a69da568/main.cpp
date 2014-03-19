#include <iostream>
#include <sstream>
#include <locale>
#include <codecvt>
 
int main()
{
  const char* u8_string = u8"双喜雙喜!";
  
  std::stringbuf data(u8_string);
  std::wbuffer_convert<std::codecvt_utf8<wchar_t>> cvt(&data);
  std::wistream cvt_stream(&cvt);
  
  std::wstring wstr;
  cvt_stream >> wstr;
  
  const wchar_t* LB_str = wstr.c_str();
  
  std::wcout.sync_with_stdio(false);
  std::wcout.imbue(std::locale("en_US.utf8"));
  std::wcout << LB_str << '\n';
}