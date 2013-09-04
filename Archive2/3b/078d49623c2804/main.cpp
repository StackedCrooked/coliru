#include <locale>
#include <iostream>
 
void try_upper(const std::ctype<wchar_t>& f, wchar_t c)
{
    wchar_t up = f.toupper(c);
    if (up != c) {
        std::wcout << "Upper case form of \'" << c << "' is " << up << '\n';
    } else {
        std::wcout << '\'' << c << "' has no upper case form\n";
    }
}
 
int main()
{
    std::locale::global(std::locale("en_US.utf8"));
    std::wcout.imbue(std::locale());
    std::wcout << "In US English UTF-8 locale:\n";
    auto& f = std::use_facet<std::ctype<wchar_t>>(std::locale());
    try_upper(f, L's');
    try_upper(f, L'ſ');
    try_upper(f, L'ß');
 
    std::wstring str = L"Hello, World!";
    std::wcout << "Uppercase form of the string '" << str << "' is ";
    f.toupper(&str[0], &str[0] + str.size());
    std::wcout << "'" << str << "'\n";
}