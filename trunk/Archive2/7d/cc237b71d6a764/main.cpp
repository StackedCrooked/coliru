#include <iostream>
#include <map>
#include <string>

int main(int argc, char* argv[])
{
    std::multimap<std::string,int> testMap;
    testMap.insert(std::pair<std::string,int>("a", 1));
    testMap.insert(std::pair<std::string,int>("a", 2));
    testMap.insert(std::pair<std::string,int>("a", 3));

    auto range = testMap.equal_range(std::string("a"));
    if(range.first != testMap.end())
    {
        --range.second;
        for (auto it = range.first; it != std::next(range.second); ++it)
        {
            testMap.insert(std::pair<std::string,int>("b", it->second));
            // this loop becomes infinite
        }
    }

    // never gets here
    for (auto it = testMap.begin(); it != testMap.end(); ++it)
    {
        std::cout << it->first << " - " << it->second << std::endl;
    }
    return 0;
}