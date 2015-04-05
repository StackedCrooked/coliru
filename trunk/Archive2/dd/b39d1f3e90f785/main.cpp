#include <algorithm>
#include <sstream>
#include <iterator>
#include <iostream>

int main() {
    std::istringstream iss("beauty shall be in ze eye of the beholder");

    std::string top2[2];
    auto end = std::partial_sort_copy(
            std::istream_iterator<std::string>(iss), {},
            std::begin(top2), std::end(top2),
            std::greater<std::string>());

    for (auto it=top2; it!=end; ++it)
        std::cout << "(Next) highest word: '" << *it << "'\n";
}
