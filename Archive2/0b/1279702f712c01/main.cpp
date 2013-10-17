#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <string>

int main()
{    
    auto c = std::map<int, std::string>{ {1, "hello"}, {2, "world"} };
    
    {   // 1) forward iteratation
        auto it = begin(c);
        for (; it != end(c); ++it){}
        std::cout << std::boolalpha << (it == c.rbegin().base()) << "\n";
    }

    {   // 2) meh, backward iteration
        auto it = end(c);
        for (; it != begin(c); --it){}
        std::cout << std::boolalpha << (it == c.rend().base()) << "\n";
    }

    {   // 2') better: reverse iteration
        auto it = c.rbegin();
        for (; it != c.rend(); ++it){}
        std::cout << std::boolalpha << (it.base() == begin(c)) << "\n";
    }

    {   // 1') backward reverse, better avoid this
        auto it = c.rend();
        for (; it != c.rbegin(); --it){}
        std::cout << std::boolalpha << (it.base() == end(c)) << "\n";
    }
}
