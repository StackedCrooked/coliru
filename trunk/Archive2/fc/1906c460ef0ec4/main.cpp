# include <iostream>
# include <string>
# include <sstream>

int main()
{
    float aValue = -1;
    std::wistringstream ss(L" 60px;");      
    ss >> aValue;
    std::wcout << bool(ss) << ' '<< aValue << std::endl;
}
