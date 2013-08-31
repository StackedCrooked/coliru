#include <string>
#include <algorithm>
#include <iostream>
#include <cctype>
#include <cstdlib>
#include <vector>

int main ()  
{
    std::vector<std::string> words = {"aaa", "bbb", "ccc"}; // PROVIDED VALUES JUST FOR THIS DEMO
    std::string inp;

    while (std::cin >> inp)
       words.push_back(inp);

    //Processing vector to make all word Uppercase
    for (int i = 0; i < words.size(); ++i)
    {
        std::string& word = words.at(i);

        std::transform(
            word.begin(),
            word.end(), 
            word.begin(), (int (&)(int)) std::toupper
        );
    }
         
    for (auto &e : words)
        std::cout << e << std::endl;
}