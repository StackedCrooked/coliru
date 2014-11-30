#include <iostream>
#include <vector>
#include <iterator>

int main() {
    std::vector<std::string> just_words(std::istream_iterator<std::string>(std::cin), {});
    for(auto s : just_words)
        std::cout << "'" << s << "'\n";
}
