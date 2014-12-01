#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>

int main() {
    std::vector<std::vector<std::string> > child_hobbies;

    unsigned n, c, f;
    if (std::cin >> n >> c >> f) {
        while (std::cin && n--) {
            child_hobbies.emplace_back();
            std::copy_n(std::istream_iterator<std::string>(std::cin), c, back_inserter(child_hobbies.back()));
        }
    }

    for(auto s : child_hobbies)
        std::copy(begin(s), end(s), std::ostream_iterator<std::string>(std::cout << "\n", ";"));
}
