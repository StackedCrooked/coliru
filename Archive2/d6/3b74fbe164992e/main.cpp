#include <iostream>
#include <algorithm>
#include <string>
#include <regex>

int main()
{
    std::string const s{ "jeaye boob const" };
    
    /* Find a single match. */
    std::regex const r1{ "boob" };
    if(std::regex_search(s, r1))
    { std::cout << "found boob" << std::endl; }
    
    /* Get info on that match. */
    std::smatch sm;
    if(std::regex_search(s, sm, r1))
    { std::cout << "found '" << sm.str() << "' at " << sm.position() << std::endl; }
    
    /* Multiple matches. */
    std::regex r2{ "([[:alpha:]])+" };
    std::sregex_iterator it{ std::begin(s), std::end(s), r2 };
    std::sregex_iterator const end{};
    for( ; it != end; ++it)
    {
        std::cout << "found word " << it->str() << std::endl
                  << "  position " << it->position() << std::endl
                  << "  length " << it->length() << std::endl;
    }
}
