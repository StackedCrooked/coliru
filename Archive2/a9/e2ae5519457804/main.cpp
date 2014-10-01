#include <iostream>
#include <string>
#include <vector>
#include <boost/locale.hpp>

int main()
{
    
    std::string in = u8"Привет";
    std::wstring strout;
    std::wstring strin = boost::locale::conv::utf_to_utf<wchar_t>(in);

    for (auto wch : strin)
        std::cout << wch << " " << std::iswalpha(wch) << std::endl;
        
    std::cout << std::endl;

    std::setlocale(LC_ALL, "ru_RU.utf8");
    std::cout << std::endl;
    for (auto wch : strin)
        std::cout << wch << " " << std::iswalpha(wch) << std::endl;
}
