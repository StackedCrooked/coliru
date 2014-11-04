#include <boost/lexical_cast.hpp>
#include <iostream>
#include <string>


void parse(std::string s)
{
    if (s.empty())
    {
        throw s;
    }
    
    char c = s.back();
    s.pop_back();
    switch (c)
    {
        case 'i': throw boost::lexical_cast<int>(s);
        case 'l': case 'L': throw boost::lexical_cast<long>(s);
    }
    
    s.push_back(c);
    throw s;
        
}


int main()
{
    try 
    {
        parse("12L");
    }
    catch (int i)
    {
        std::cout << "got int " << i << std::endl;
    }
    catch (long l)
    {
        std::cout << "got long " << l << std::endl;
    }
    catch (std::string s)
    {
        std::cout << "got string " << s << std::endl;
    }
}
