#include <iostream>


std::string escape(const std::string & s)
{
    std::string result;
    result.reserve(2 * s.size());
    for (auto c : s)
    {
        if (c == '\t')
        {
            result.push_back('\\');
            result.push_back('t');
        }
        else
        {
            result.push_back(c);
        }
    }
}

int main()
{
    std::cout << escape("abc\tdef") << std::endl;
}