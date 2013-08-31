#include <string>
#include <iostream>

int main() {
    std::wstring ws(L"F:\\右旋不规则.pdf");
    std::wcout << ws << std::endl;
    std::wcout << ws.data() << std::endl;
}