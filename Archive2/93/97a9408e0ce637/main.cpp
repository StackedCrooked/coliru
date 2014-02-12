#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <sstream>

std::map<int, std::vector<std::string>> foo()
{
    std::map<int,std::vector<std::string>> m;
    for (int i=0; i<100; ++i)
    {
        
        std::ostringstream oss;
        for (int j=0; j<10; ++j)
            oss << i;
        m[42].push_back(oss.str());
    }
    return m;
}


int main()
{
    // auto m = foo();

    for (const std::string& i : foo()[42])
    {
        std::cout << i << std::endl;
    }

    /*BOOST_FOREACH(const std::string& i, m[42])
    {
        std::cout << i << std::endl;
    }*/
}