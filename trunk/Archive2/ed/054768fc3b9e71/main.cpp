#include <locale>
#include <iostream>

int main()
{
    const  wchar_t c = 192; // LATIN CAPITAL LETTER A WITH GRAVE
    const std::locale locales[] = {std::locale("C"), std::locale("C.UTF-8")};
    for (const auto &l: locales)
    {
        std::cout << "Extended ASCII(" << c << ")" << " is " << (std::isupper(c, l) ? "" : "not ") << "uppercase in locale " << l.name() << std::endl;
    }
}
