#include <iostream>
#include <map>
#include <vector>

template <typename InputIt>
struct key_it : public InputIt {
    key_it(InputIt it) : InputIt(it) {}
    auto operator*() { return (*this)->first; }
};

// Helper function for making key iterators.
template <typename InputIt>
key_it<InputIt> make_key_it(InputIt it) {
    return {it};
}

int main() {
    std::map<int, char> m{{1, 'a'}, {2, 'b'}, {3, 'c'}};
    std::vector<int> v{make_key_it(std::begin(m)), make_key_it(std::end(m))};

    for (auto i : v) {
        std::cout << i << std::endl;
    }
}