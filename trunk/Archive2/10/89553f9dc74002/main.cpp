#include <string>
#include <vector>
template<typename It>
void main_(It argv_begin, It argv_end);
int main(int argc, char const** argv) {
    std::vector<std::string> argv_vector(argv, argv + argc);
    main_(argv_vector.begin(), argv_vector.end());
    return 0;
}
#define main main_

// usage example
#include <iostream>
#include <string>
#include <vector>

template<typename It>
void main(It argv_begin, It argv_end) {
    for (auto it = argv_begin; it != argv_end; ++it) {
        std::cout << *it << '\n';
    }
}