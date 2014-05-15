#include <iostream>
#include <sstream>
#include <locale>
#include <iomanip>
#include <ctime>
 
int main()
{
    std::tm t;
    std::istringstream ss("2011-Februar-18 23:12:34");
    ss.imbue(std::locale("de_DE"));
    ss >> std::get_time(&t, "%Y-%b-%d %H:%M:%S");
    std::cout << std::put_time(&t, "%c") << '\n';
}