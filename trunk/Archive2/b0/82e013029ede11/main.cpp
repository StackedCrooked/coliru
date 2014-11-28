#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <boost/algorithm/string.hpp>

int main()
{
    std::vector<std::string> words;
    std::string sentence = "This__should_______be____split_into____seven___strings";
    boost::split(words, sentence, boost::is_any_of("_"));
    words.erase(std::remove_if(words.begin(), words.end(), [](const std::string &s){return s.empty();}));
    for (const auto &word : words)
    {
        std::cout << word << std::endl;
    }
}
