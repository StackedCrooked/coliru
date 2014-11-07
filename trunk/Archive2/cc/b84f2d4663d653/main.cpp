#include <cctype>
#include <iterator>

template <typename It, typename F>
It tokenize(It first, It const last, F const& fun) {
    while (first != last) {
        auto s   = first;
        auto len = 0ull;
        while (first!=last && !std::isspace(static_cast<unsigned char>(*first))) ++len, ++first;
        fun(s,first,len);
        while (first!=last && std::isspace(static_cast<unsigned char>(*first))) ++first;;
    }
    return first;
}

template <typename R, typename F> void tokenize(R const& range, F const& f) {
    tokenize(std::begin(range), std::end(range), f);
}

#include <iostream>
#include <boost/utility/string_ref.hpp>
    
int main() {
    tokenize("hortus racecar musicus religiosus", [](auto start, auto end, size_t len) {
        if (len>=6 && len<=12) {
            boost::string_ref s(start,len); // or std::string(start,end) for non-char*
            end = start + len/2+1;
            if (end == std::mismatch(start, end, s.rbegin()).first)
                std::cout << len << ": " << s << "\n";
        }
    });
}

