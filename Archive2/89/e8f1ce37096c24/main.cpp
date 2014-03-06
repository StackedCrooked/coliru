#include <iostream>
#include <locale>

int main()
{
    setlocale(LC_ALL, "en_US.utf8");
    const unsigned int x = 123456;
    
    std::cout.imbue(std::locale("en_US.utf8"));
    std::cout << std::fixed << x << '\n';
}
