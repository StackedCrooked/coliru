#include <iostream>
int main()
{
    std::wcout << ( L"Hello" + (wchar_t)0x0002 ) << std::endl;
}
