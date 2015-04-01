#include <iostream>
#include <boost/regex.hpp>
#include <boost/algorithm/string_regex.hpp>
#include <vector>

int main() {
    std::string const sentence = "My dog Fluffy\\ Cake likes to jump";

    std::vector<std::string> words;
    boost::algorithm::split_regex(words, sentence, boost::regex("(?<!\\\\)\\s"), boost::match_default);

    for (auto& w : words)
        std::cout << " '" << w << "'\n";
}
