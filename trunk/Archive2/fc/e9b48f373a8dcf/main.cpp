#include <iostream>
#include <clocale>
#include <cstdlib>
 
int main()
{
    std::setlocale(LC_ALL, "en_US.utf8");
    // UTF-8 narrow multibyte encoding
    const wchar_t* wstr = L"z\u00df\u6c34\U0001d10b РОМАН"; // or L"zß水𝄋"
    char mbstr[100];
    size_t size =  std::wcstombs(mbstr, wstr, 100);
    std::cout << "multibyte string: " << mbstr << '\n';
    std::cout << size<< '\n';
}