#include <iostream>
#include <string>
#include <set>

void replace(std::string &s, char replacer, std::set<char> &replacies);

int main()
{
    std::string my_string = "Hello World !!! ... Hello.?";

    std::cout << my_string << std::endl;

    std::set<char> my_set = {'!', '.', '?',','};

    replace(my_string, ' ', my_set);

    std::cout << my_string << std::endl;

    return 0;
}

void replace(std::string &s, char replacer, std::set<char> &replacies)
{
    for (int i=0; i < s.size(); i++)
        if (replacies.count(s[i])) s[i] = replacer;

}

