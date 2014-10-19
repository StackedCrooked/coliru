template<typename InputIt, typename OutputIt, typename Predicate>
OutputIt copy_until(InputIt first, InputIt last, OutputIt out, Predicate pred) {
    for(; first != last; ++first, ++out) {
        if(pred(*first))
            break;
        *out = *first;
    }
    return out;
}

#include <string>
#include <istream>
#include <iterator>
#include <cctype>

class WordExtractor {
public:
    WordExtractor(std::istream& stream) : stream(stream) {}

    std::string next() {
        std::string word;
        copy_until(std::istreambuf_iterator<char>{stream}, std::istreambuf_iterator<char>{}, std::back_inserter(word), [](char c) { return !std::isalpha(c); });
        if(stream)
            stream.ignore(1);
        return word;
    }

private:
    std::istream& stream;
};

#include <sstream>
#include <iostream>

int main() {
    std::istringstream stream("Hello_World");
    WordExtractor words(stream);
    for(std::string word = words.next(); !word.empty(); word = words.next()) {
        std::cout << word << '\n';
    }
}
