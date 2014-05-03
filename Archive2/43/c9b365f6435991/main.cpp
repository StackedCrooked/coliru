#include <cstdint>

constexpr const std::uint8_t major = 1;
constexpr const std::uint8_t minor = 10;
constexpr const std::uint8_t bugfix = 0;

struct char_array {
    constexpr char_array() : ofs{sizeof(value) - 1}, value{} {}
    constexpr const char* c_str() const { return value + ofs; }

    constexpr void push_front(char c) {
        --ofs;
        value[ofs] = c;
    }

private:
    int ofs;
    char value[42]; // big enough to hold version string
};

constexpr char_array predend_int(char_array a, int x) {
    do {
        auto digit = x % 10;
        x = x / 10;
        a.push_front(digit + '0');
    }
    while (x);
    return a;   
}

constexpr auto version_string() {
    char_array a;
    a = predend_int(a, bugfix);
    a.push_front('.');
    a = predend_int(a, minor);
    a.push_front('.');
    a = predend_int(a, major);
    return a;
}

#include <iostream>
int main() {
    constexpr char_array ver = version_string();
    std::cout << ver.c_str() << '\n';
}