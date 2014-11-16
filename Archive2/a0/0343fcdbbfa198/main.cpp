#include <iostream>
#include <locale>
 
void try_with(wchar_t c, const char* loc)
{
    std::wcout << "isspace('" << c << "', locale(\"" << loc << "\")) returned "
               << std::boolalpha << std::isspace(c, std::locale(loc)) << '\n';
}
 
int main()
{
    const wchar_t EM_SPACE = L'\u2003'; // Unicode character 'EM SPACE'
    try_with(EM_SPACE, "C");
    try_with(EM_SPACE, "en_US.UTF8");
}