#include <iostream>
#include <iterator>

template <class OutputIterator>
void components_of(int value, OutputIterator out) {
    
    int pos = 0;

    while(value) {
        if (value & 1) 
            *out++ = pos;
        value >>= 1;
        ++pos;
    }
}

int main() {
    components_of(5, std::ostream_iterator<int>(std::cout, "\t"));
}
