#include <iterator>
#include <ostream>
#include <utility>
#include <string>

template <class charT, class traits = std::char_traits<charT>>
struct cool_ostream_iterator : std::iterator<std::output_iterator_tag, void, void, void, void> {
private:
    using ostream_type = std::basic_ostream<charT,traits>;

public:
    cool_ostream_iterator(ostream_type& os) noexcept : os(&os) {}
    template <typename T>
    cool_ostream_iterator& operator=(T&& t) {
        (*os) << std::forward<T>(t) << '\n';
        return *this;
    }
    cool_ostream_iterator& operator*() {
        return *this;
    }
    cool_ostream_iterator& operator++() {
        return *this;
    }
    cool_ostream_iterator& operator++(int) {
        return *this;
    }

private:
    ostream_type* os;
};

#include <vector>
#include <algorithm>
#include <iostream>
int main() {
    std::vector<int> is { 1, 2, 3 };
    std::vector<std::string> ss { "a", "b", "c" };

    cool_ostream_iterator<char> it(std::cout);
    it = std::copy(is.begin(), is.end(), it);
    std::copy(ss.begin(), ss.end(), it);
}