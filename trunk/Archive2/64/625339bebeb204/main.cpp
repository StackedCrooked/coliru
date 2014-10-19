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

std::string next_word(std::istream& stream) {
    std::string word;
    copy_until(std::istreambuf_iterator<char>{stream}, std::istreambuf_iterator<char>{}, std::back_inserter(word), [](char c) { return !std::isalpha(c); });
    if(stream)
        stream.ignore(1);
    return word;
}

#include <sstream>
#include <iostream>

int main() {
    std::istringstream stream("Hello_World");
    for(std::string word = next_word(stream); !word.empty(); word = next_word(stream)) {
        std::cout << word << '\n';
    }
}
