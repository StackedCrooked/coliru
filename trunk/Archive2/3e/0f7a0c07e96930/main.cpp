#include <iostream>
#include <vector>
#include <algorithm> 

int main() {
    std::vector<std::wstring> elements = {L"1",L"2",L"3",L"4",L"5"}; // next values inside L"1",L"2",L"3",L"4",L"5"
    std::wstring value = L"3";
    
    bool result = std::binary_search(elements.begin(), elements.end(), value.c_str());
    
    std::cout << (result?"found":"not found");
    
    return 0;
}