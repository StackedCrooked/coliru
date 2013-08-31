#include <algorithm>
#include <string>
#include <wctype.h>
#include <iostream>
int main() {
    std::wstring data = L"Straße";
    std::wcout << data.size() << '\n';
    std::transform(data.begin(), data.end(), data.begin(), ::towupper);
    std::wcout << data << '\n';
    std::wcout << data.size() << '\n';
}