#include <string>
#include <sstream>
#include <iostream>

int main()
{
    std::wistringstream wss(L"42");
    int i;
    if((wss >> i) && wss.eof()) {
        std::cout << i << '\n';
    }
}
