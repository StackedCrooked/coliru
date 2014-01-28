#include <algorithm>
#include <string>
#include <vector>
#include <map>

static std::map<std::string, int> exclusions;
static std::vector<std::string> titles;

bool isExclusion(std::string word)
{
    try
    {
        exclusions.at(word);    
    }
    catch (std::out_of_range e)
    {
        return true;
    }

    return false;
}

#include <iostream>
//#include "titles.h"

int main()
{
    exclusions["is"] = 1;
    exclusions["the"] = 1;
    exclusions["of"] = 1;
    exclusions["and"] = 1;
    exclusions["a"] = 1;
    exclusions["but"] = 1;
    exclusions["as"] = 1;

    titles.push_back("Descent of Man");
    titles.push_back("The Ascent of Man");
    titles.push_back("The Old Man and The Sea");
    titles.push_back("A Portrait of the Artist As a Young Man");
    titles.push_back("A Man is a Man but Bubblesort IS A DOG");
    std::sort(titles.begin(), titles.end());

    try
    {
        exclusions.at("the");
    }
    catch(std::out_of_range e)
    {
        std::cout << "Not found\n";
    }
    std::cout << "Exclusion?: " << isExclusion("hello") << std::endl;
    std::cout << "Exclusion?: " << isExclusion("the") << std::endl;

    for(auto i = titles.begin(); i != titles.end(); i++)
    {
        std::cout << *i << "\n";
    }

    return 0;
}