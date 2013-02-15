#include <vector>
#include <algorithm>
#include <iostream>
#include <functional>
#include <iterator>
#include <iomanip>

template<typename charT, typename traits = std::char_traits<charT> >
class center_helper;

template<typename a, typename b>
std::basic_ostream<a, b>& operator<<(std::basic_ostream<a, b>& s, const center_helper<a, b>& c);

template<typename charT, typename traits >
class center_helper {
    std::basic_string<charT, traits> str_;
public:
    center_helper(std::basic_string<charT, traits> str) : str_(str) {}
    template<typename a, typename b>
    friend std::basic_ostream<a, b>& operator<<(std::basic_ostream<a, b>& s, const center_helper<a, b>& c);
};

template<typename charT, typename traits = std::char_traits<charT> >
center_helper<charT, traits> centered(std::basic_string<charT, traits> str) {
    return center_helper<charT, traits>(str);
}

// redeclare for std::string directly so we can support anything that implicitly converts to std::string
center_helper<std::string::value_type, std::string::traits_type> centered(const std::string& str) {
    return center_helper<char>(str);
}

template<typename charT, typename traits = std::char_traits<charT> >
std::basic_ostream<charT, traits>& operator<<(std::basic_ostream<charT, traits>& s, const center_helper<charT, traits>& c) {
    std::streamsize w = s.width();
    if ( (int) w > (int)c.str_.length()) {
        std::streamsize left = (w + c.str_.length()) / 2;
        s.width(left);
        s << c.str_;
        s.width(w - left);
        s << "";
    } else {
        s << c.str_;
    }
    return s;
}

int main() 
{
    std::cout << "|" << std::setw(10) << centered("Table")
              << "|" << std::setw(10) << centered("Column")
              << "|" << std::setw(9)  << centered("Header") << "|"
              << std::endl;
}