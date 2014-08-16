#include <iostream>
#include <chrono>

template<typename CharT, typename Traits>
std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const std::chrono::duration<long double>& d) {
    return os << d.count() << 's';
}

template<typename CharT, typename Traits, typename Rep, typename Period>
std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const std::chrono::duration<Rep, Period>& d) {
    return os << std::chrono::duration_cast<std::chrono::duration<long double>>(d);
}

int main() {
    using namespace std::chrono_literals;

    std::cout << 12h + 34min + 3s << std::endl;
}