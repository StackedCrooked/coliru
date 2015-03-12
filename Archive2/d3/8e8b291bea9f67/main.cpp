#include <iostream>
#include <iterator>

template<class T, class OutputIterator>
void components_of(T value, OutputIterator out) {
    while (value) {
        T no_lowest_bit = value & (value - 1);
        *out++ = value ^ no_lowest_bit;
        value = no_lowest_bit;
    }
}

int main(int argc, char** argv) {
    components_of(51, std::ostream_iterator<int>(std::cout, "\t"));
}
