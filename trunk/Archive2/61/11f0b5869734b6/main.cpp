#include <string>
#include <iostream>
 
int main() {
    double f = 23.43000000001;	
    std::wstring f_str = std::to_wstring(f);
    std::wcout << f_str;
}