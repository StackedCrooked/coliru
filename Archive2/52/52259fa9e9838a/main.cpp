#include <iostream>
#include <locale>

int main()
{
    std::locale::global (std::locale ("en_US.UTF-8"));
    std::cout << "ي" << std::endl;
    std::wcout << L"ي" << std::endl;
}

