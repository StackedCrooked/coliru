#include <iostream>
#include <iomanip>
#include <string>

void p(std::wstring s, int w)
{
   std::wcout << std::left << std::setw(w) << s;
}

int main(int argc, char const *argv[])
{
   std::locale loc("en_US.UTF-8");
   std::wcout.imbue(loc);
   
   p(L"COL_A", 7);
   p(L"COL_B", 7);
   p(L"COL_C", 5);
   std::wcout << std::endl;
   p(L"ABC", 7);
   p(L"ÅÄÖ", 7);
   p(L"ABC", 5);
   std::wcout << std::endl;
   return 0;
}