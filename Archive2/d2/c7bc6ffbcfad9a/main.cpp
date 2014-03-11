#include <iostream>

using namespace std;

int main()
{
    wchar_t wstr[] = L"Cyrillic lowercase a is: \u0430.";
    wcout << wstr;
}
