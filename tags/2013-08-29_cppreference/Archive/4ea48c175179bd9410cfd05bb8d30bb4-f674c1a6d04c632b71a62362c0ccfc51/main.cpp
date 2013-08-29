#include <iostream>
#include <sstream>
#include <locale>

std::wostream& manipulator(std::wostream& os)
{
    os << " ";
    return os;
}

int main()
{
    std::wstringstream s2;    
    wchar_t waTemp2[4] = {0xA0, 0xA1, 0x00A2, 0xA3};
    for (int i = 0; i < 4; i++)
    {
       s2 << std::hex << (unsigned)waTemp2[i] << manipulator;
    }
    std::wstring strData2 =  s2.str();
    std::wcout << strData2.c_str() << std::endl; 
    return 0;
}