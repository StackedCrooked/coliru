#include <iostream>
#include <iomanip>
#include <ctime>
 
int main()
{
    std::time_t t = std::time(nullptr);
    std::tm tm = *std::localtime(&t);
    std::cout.imbue(std::locale("ru_RU.utf8"));
    std::cout << "ru_RU: " << std::put_time(&tm, "%c %Z") << '\n';
    std::cout.imbue(std::locale("ja_JP.utf8"));
    std::cout << "ja_JP: " << std::put_time(&tm, "%c %Z") << '\n';
}