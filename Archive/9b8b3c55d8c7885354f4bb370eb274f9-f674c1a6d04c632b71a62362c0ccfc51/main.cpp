#include <iostream>
#include <sstream>
#include <locale>

int main()
{
    std::wstringstream s2;    
    wchar_t waTemp2[4] = {0xA0, 0xA1, 0x00A2, 0xA3};
    for (int i = 0; i < 4; i++)
    {
       s2.operator<<(std::hex).operator<<((unsigned)waTemp2[i]);
    }
    std::wstring strData2 =  s2.str();
    std::wcout << strData2.c_str() << std::endl; 
    return 0;
}