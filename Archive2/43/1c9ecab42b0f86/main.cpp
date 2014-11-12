#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<std::wstring> stuff = {
        L"1", L"2", L"3", L"4", L"5"
    };
    
    if(std::binary_search(std::begin(stuff), std::end(stuff), std::wstring(L"3"))) {
        std::cout << "Found\n";
    }
    else {
        std::cout << "Not found\n";
    }
}