#include <iostream>
#include <locale>

int main()
{
    setlocale(LC_ALL, "en_US");
    const unsigned int x = 123456;
    
    std::cout.imbue(std::locale(""));
    std::cout << std::fixed << x << '\n';
}
