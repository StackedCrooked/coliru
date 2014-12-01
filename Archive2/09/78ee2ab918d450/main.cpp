#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

int main() {
    std::vector<std::vector<std::string> > child_hobbies;

    unsigned n, c, f;
    if (std::cin >> n >> c >> f && std::cin.ignore(1u<<10, '\n')) {
        std::string line;
        while (n-- && std::getline(std::cin, line)) {
            std::istringstream iss(line);
            std::istream_iterator<std::string> f(iss), l;
            child_hobbies.emplace_back(f,l);

            assert(child_hobbies.back().size() == c); // verify
        }
    }

    for(auto s : child_hobbies)
        std::copy(begin(s), end(s), std::ostream_iterator<std::string>(std::cout << "\n", ";"));
}
