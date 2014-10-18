#include <iostream>
#include <locale>

int main()
{
    std::locale loc = std::locale ("en_US.UTF-8");
    std::wcout.imbue(loc);
    std::cout << "ي" << std::endl; //OK!
    std::wcout << "ي" << std::endl;
    std::wcout << "L specifier = " << L"ي" << std::endl;
    std::wcout << "u specifier = " << u"ي" << std::endl;
    std::wcout << "u8 specifier = " << u8"ي" << std::endl;
}

