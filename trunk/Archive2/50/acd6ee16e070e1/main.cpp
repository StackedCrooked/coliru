#include <iostream>
#include <string>

int main()
{
    std::wstring ws(L"Hello World");
    std::string s(ws.begin(), ws.end());
    
    std::wcout << "ws: " << ws << std::endl;
    std::cout  << "s:  " << s  << std::endl;
}
