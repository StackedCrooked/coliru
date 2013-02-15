#include <string>
#include <cstdint>
#include <algorithm>
#include <iostream>
#include <cassert>

template <typename T> T to_integer(std::string const& s) {
    static_assert(!std::numeric_limits<T>::is_signed, "unsigned only");
    return std::accumulate(begin(s), end(s), T{0},
            [](T accu, char c) { c-='0'; assert(c>=0 && c<10); return (10*accu)+c; });
}

int main()
{
    std::cout << to_integer<unsigned>("1230") << "\n";
    std::cout << to_integer<unsigned long>("00976348") << "\n";
}