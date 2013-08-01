#include <algorithm>
#include <string>
#include <wctype.h>
#include <iostream>
int main() {
    std::wstring data = L"Schloß";
    std::transform(data.begin(), data.end(), data.begin(), ::towupper);
    std::wcout << data;
}