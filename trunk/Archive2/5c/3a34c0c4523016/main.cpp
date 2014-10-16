#include <iostream>
#include <locale>

int main()
{
    std::locale::global (std::locale ("en_US.UTF-8"));
#if DEF != 2
    std::cout << "ي" << std::endl;
#endif
#if DEF != 1
    std::wcout << L"ي" << std::endl;
#endif
}
