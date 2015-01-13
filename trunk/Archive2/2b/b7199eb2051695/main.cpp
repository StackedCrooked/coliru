#include <iostream>
#include <string>
#include <boost/xpressive/xpressive.hpp>
using namespace boost::xpressive;
using regex = sregex;

struct regex_builder
{
    regex xx;
    std::string str;

    void BeginCompilation()
    {
    }

    void AddFloat()
    {
        str += R"___([+-]?\d+(?:\.?(?:\d+)?(?:[e|E][+-]?\d+)?)?)___";
    }

    void AddInteger()
    {
        str += R"___([+-]?\d+)___";
    }

    void AddHexInteger()
    {
        str += R"___([+-]?[\dA-Fa-f]+)___";
    }

    void AddString()
    {
        str += R"___(\w+)___";
    }

    void AddChar()
    {
        str += R"___(\w)___";
    }

    void AddSpace()
    {
        str += R"___(\s+)___";
    }

    void FinishCompilation()
    {
        str += R"___(\s*)___";
    }

    template<class ForwardIt>
    ForwardIt CompileRegexy(ForwardIt begin, ForwardIt end)
    {
        auto it = begin;
        if(*it == '{')
        {
            size_t count = 0;
            for(auto prev = *it++; it != end; prev = *it++)
            {
                if(prev != '\\')
                {
                    if(*it == '}')
                    {
                        if(count == 0) break;
                        else --count;
                    }
                    else if(*it == '{') ++count;
                }
                str.push_back(*it);
            }
        }
        return it;
    }

    template<class ForwardIt>
    void Compile(ForwardIt begin, ForwardIt end)
    {
        std::string output;
        output.reserve(std::distance(begin, end) * 3);
        
        BeginCompilation();
        for(auto it = begin; it != end; ++it)
        {
            if(*it == '%')
            {
                if(std::next(it) != end)
                {
                    switch(*++it)
                    {
                        case 'x': case 'X':
                            AddHexInteger(); break;
                        case 'd':
                            AddInteger(); break;
                        case 'f':
                            AddFloat(); break;
                        case 's':
                            AddString(); break;
                        case 'c':
                            AddChar(); break;
                        case '$':
                            it = CompileRegexy(std::next(it), end); break;
                    }
                }
            }
            else if(*it == ' ')
                AddSpace();
            else
                str.push_back(*it);
        }
        FinishCompilation();
    }
    
    void Compile(const std::string& rgx)
    {
        return Compile(rgx.begin(), rgx.end());
    }

};

int main()
{
    regex_builder test;
    test.Compile("%d %s %s %s %s %s %s %s %d %d %x(?: %d)?(?: %f)?(?: %f)?(?: %d)?");
    std::cout << test.str << std::endl;
}
