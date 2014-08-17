#include <regex>
#include <iostream>
int main()
{
    std::smatch matches;
    std::string s = "y=a^b,z=(y+76),k=(z|p)";
    std::regex  expr(R"((\w+)=\((\w+)([\|&\^\+\-\*])(\w+)\))");

    for(auto it = std::sregex_iterator(s.begin(), s.end(), expr);
             it != std::sregex_iterator();
           ++it)
    {
         std::cout << "Found a match: " << it->str() << "\n";
         std::smatch m = *it;

         std::cout << "prefix=[" << m.prefix() << "]\n";
         for(std::size_t n = 0; n < m.size(); ++n)
                 std::cout << "   m[" << n << "]=[" << m[n] << "]\n";
         std::cout << "suffix=[" << m.suffix() << "]\n";
    }
}
