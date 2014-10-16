#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <locale>

#define USE_CODECVT 0
#define USE_IMBUE   1

#if USE_CODECVT
#include <codecvt>
#endif 
using namespace std;

int main()
{
#if USE_CODECVT
    locale ru("ru_RU.utf8", new codecvt_utf8<wchar_t, 0x10ffff, consume_header>{});
#else
    locale ru("ru_RU.utf8");
#endif
#if USE_IMBUE
    wcout.imbue(ru);
#else
    locale::global(ru);
#endif
    wstringstream in{L"Преступление и наказание"};
    in.imbue(ru);
    wstring word;
    unsigned wordcount = 0;
    while (in >> word) {
        wcout << wordcount << ": \"" << word << "\"\n";
        ++wordcount;
    }
    wcout << "\nI counted " << wordcount << " words.\n"
        << "and the last word was \"" << word << "\"\n";
}