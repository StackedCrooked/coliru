#include <map>
#include <string>
#include <iostream>

void f(std::map<std::string, std::string> m = {})
{
        std::cout << m.size() << std::endl;
        for (const auto& s: m) {
                std::cout << s.first << "->" << s.second <<"\n";
        }
}

int main()
{
        f();
}
