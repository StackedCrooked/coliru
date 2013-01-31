#include <algorithm>
#include <cassert>
#include <cstring>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

template<typename InputIter, typename OutputIter, typename Pred>
OutputIter
copy_while(InputIter begin, InputIter end, OutputIter result, Pred pred)
{
    while (begin != end)
    {
        typename std::iterator_traits<InputIter>::value_type value = *begin;
        if (!pred(value))
            break;
        *result = value;
        result++;
        begin++;
    }
    return result;
}

struct seq {
    std::vector<char> v;
    using value_type = char;

    void push_back(char c) { v.push_back(c); }

    bool operator ==(char const* other) const {
        return v.size() == std::strlen(other) and
            std::equal(v.begin(), v.end(), other);
    }

    bool empty() const { return v.empty(); }
};

inline bool
is_valid_seq_char(char c)
{ return std::string("ACGT").find(c) != std::string::npos; }

inline std::istream&
operator>>(std::istream& in, seq& rhs)
{
    copy_while(std::istreambuf_iterator<char>(in), {},
            std::back_inserter(rhs), &is_valid_seq_char);
    if (rhs.empty())
        in.setstate(std::ios::failbit);  // no seq in stream
    return in;
}

int main() {
    /* string */ {
        std::istringstream istr("GATTACA");
        std::string s;
        assert((istr >> s) and s == "GATTACA");
        assert(istr.eof());
    }

    /* seq */ {
        std::istringstream istr("GATTACA");
        seq s;
        assert((istr >> s) and s == "GATTACA");
        assert(istr.eof());
    }
}
