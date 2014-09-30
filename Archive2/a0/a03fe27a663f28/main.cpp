#include <iostream>
#include <string>
#include <regex>
 
int main()
{
    std::string lines = "//#if BLA\n#elif LALALA\n";
 
    std::regex e("\n(?:?!//)#(?:if|elif)(?:\\s)*([A-Z]+)");
 
    std::smatch m;

    
    while (std::regex_search (lines,m,e))
    {
        for (auto x:m) std::cout << x << " ";
        std::cout << std::endl;
        lines = m.suffix().str();
    }
}