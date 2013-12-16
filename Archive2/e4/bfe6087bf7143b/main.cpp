#include <cstdio>
#include <clocale>
#include <ctime>
#include <cwchar>
 
int main()
{
    // the C locale will be UTF-8 enabled English;
    // decimal dot will be German
    // date and time formatting will be Japanese
    std::setlocale(LC_ALL, "C");
    std::setlocale(LC_NUMERIC, "de_DE");
    std::setlocale(LC_TIME, "ja_JP");
 
    wchar_t str[100];
    std::time_t t = std::time(NULL);
    std::wcsftime(str, 100, L"%A %c", std::localtime(&t));
    std::wprintf(L"Number: %.2f\nDate: %Ls\n", 3.14, str);
}