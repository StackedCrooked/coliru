#include <cctype>
#include <iterator>

template <typename It, typename F>
    void tokenize(It& first, It const last, F const& f)
{
    while (first != last)
    {
        auto s   = first;
        auto len = 0ull;
        while (first!=last && !std::isspace(static_cast<unsigned char>(*first))) ++len, ++first;
        f(s,first,len);
        while (first!=last && std::isspace(static_cast<unsigned char>(*first))) ++first;;
    }
}

template <typename Range, typename F>
    void tokenize(Range const& range, F const& f)
{
    using std::begin;
    using std::end;
    auto b(begin(range));
    tokenize(b, end(range), f);
}

#include <string>
#include <iostream>
#include <boost/utility/string_ref.hpp>
    
int main()
{
    std::string corpus = "hortus racecar musicus religiosus";

    std::ostreambuf_iterator<char> out(std::cout);

    tokenize("hortus racecar musicus religiosus", [&](auto start, auto end, size_t len) {
        if (len>=6 && len<=12) 
        {
            std::string s(start,end);
            if (s.end() == std::mismatch(s.begin(), s.end(), s.rbegin()).first)
                std::cout << len << ": " << std::string(start,end) << "\n";
        }
    });
}
