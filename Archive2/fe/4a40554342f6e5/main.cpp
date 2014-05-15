#include <cstddef>
#include <cstdint>
#include <iostream>
#include <type_traits>

int main() {
    std::cout << "align of uint32_t    = " << std::alignment_of<std::uint32_t>::value << std::endl;
    std::cout << "align of uint64_t    = " << std::alignment_of<std::uint64_t>::value << std::endl;
    std::cout << "align of long double = " << std::alignment_of<long double>::value << std::endl;
    std::cout << "align of max_align_t = " << std::alignment_of<max_align_t>::value << std::endl;
    return 0;
}
