#include <utility>
#include <iostream>
#include <iterator>

struct T : std::pair<float, int> {
    using std::pair<float, int>::pair;
};

std::istream& operator>>(std::istream& stream, T& in) {
    return stream >> in.first >> in.second;
}

int main() {
    std::istream_iterator<T> iit(std::cin);
    std::istream_iterator<T> eos;
    while (iit != eos) {
        std::cout << (*iit).first << std::endl;
        ++iit;
    }
}
