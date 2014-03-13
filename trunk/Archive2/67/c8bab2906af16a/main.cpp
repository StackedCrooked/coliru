#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

template<class hay_iterator, class needle_iterator>
std::vector<std::string> tokenize(hay_iterator search_begin, hay_iterator search_end, needle_iterator delimeter_begin, needle_iterator delimeter_end) {
    std::vector<std::string> tokens;
    auto delimeter_size = std::distance(delimeter_begin, delimeter_end);
    auto position = search_begin;
    while(position != search_end) {
        auto delim = std::search(position, search_end, delimeter_begin, delimeter_end);
        if(delim == search_end) {
            break;
        } else {
            auto token = std::string(position, delim);
            tokens.push_back(token);
        }
    }
    return tokens;
}

int main() {
    std::string test = "one;two;three;four";
    std::string delimeter = ";";
    for(auto token : tokenize(test.begin(), test.end(), delimeter.begin(), delimeter.end())) {
        std::cout << token;
    }
    return 0;
}