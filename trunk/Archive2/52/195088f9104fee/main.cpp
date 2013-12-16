#include <iostream>
#include <vector>
#include <clocale>
#include <cwchar>
 
void print_as_wide(const char* mbstr)
{
    std::mbstate_t state = std::mbstate_t();
    int len = 1 + std::mbsrtowcs(NULL, &mbstr, 0, &state);
    wchar_t wstr[100];
    std::mbsrtowcs(wstr, &mbstr, len, &state);
    std::wcout << "Wide string: " << wstr << '\n' ;
              
}
 
int main()
{
    std::setlocale(LC_ALL, "en_US.utf8");
    const char* mbstr =  "zbyněk,Bednář";  
    print_as_wide(mbstr);
}