#include <map>
#include <iterator>
#include <iostream>

int main() {
    std::map<char, size_t> histo;
    for(std::istream_iterator<std::string> f(std::cin),l; f!=l; histo[0] = std::max(histo[0], histo[(*f++)[0]]++));
    for(auto e : histo) if (std::isgraph(e.first)) std::cout << e.first << ": " << std::string(e.second*(80.0/histo[0]), '-') << " (" << e.second << ")\n";
}

