#include <iostream>
#include <locale>

int main()
{
    std::locale loc = std::locale ("en_US.UTF-8");
    std::wcout.imbue(loc);
    std::cout << "ي" << std::endl; //OK!
    std::wcout << "ي" << std::endl;
    std::wcout << "L = " << L"ي" << std::endl;
    std::wcout << "u = " << u"ي" << std::endl;
    std::wcout << "u8 = " << u8"ي" << std::endl;
}

