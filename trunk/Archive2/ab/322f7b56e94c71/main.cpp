#include <string>
#include <fstream>
#include <iostream>

int main() {
    std::wstring s = L"path";
    std::string ansi{ begin(s), end(s) };
    std::ifstream fl { ansi, std::fstream::in };
    std::cout << bool(fl);
}