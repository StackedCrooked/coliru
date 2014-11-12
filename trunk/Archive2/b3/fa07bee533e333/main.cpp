#include <string>
#include <iostream>

int main() {
    std::wstring Pfad;
    std::wcin >> Pfad;
    auto file = Pfad + L"*.quiz";
}