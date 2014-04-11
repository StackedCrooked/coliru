#include <iostream>
#include <type_traits>
#include <iomanip>

template <typename T>
void print_code_units(T const* str) {
    using unsigned_it = typename std::make_unsigned<T>::type;
    while(*str) {
        std::cout << std::hex << std::setw(sizeof(T)*2) << std::setfill('0') << unsigned(unsigned_it(*str)) << " ";
        ++str;
    }
    std::cout << "\n";
}

int main() {
    print_code_units(u8"Здравствулте мир 😂");
    print_code_units(u"Здравствулте мир 😂");
    print_code_units(U"Здравствулте мир 😂");
}