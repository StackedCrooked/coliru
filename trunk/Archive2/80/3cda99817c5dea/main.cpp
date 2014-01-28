#include <iostream>
#include <sstream>
#include <string>
#include <locale>
#include <ctime>
#include <iomanip>
int main()
{
    std::wstring input = L"2011-Februar-18 23:12:34";
    std::tm t;
    std::wistringstream ss(input);
    ss.imbue(std::locale("de_DE"));
    ss >> std::get_time(&t, L"%Y-%b-%d %H:%M:%S"); // uses std::time_get<wchar_t>
    std::cout << std::asctime(&t);
}