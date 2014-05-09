#include <iostream>
#include <iterator>
#include <set>
#include <sstream>
#include <string>

template <class _II, class _OI>
    static _OI escapeSomeChars(const _II inIt, const _II endIt, _OI outIt)
{
    for (_II it=inIt; it!=endIt; ++it)
        switch (*it)
        {
            case '\0': outIt++ = '\\'; outIt++ = '0'; break;
            case '\n': outIt++ = '\\'; outIt++ = 'n'; break;
            case '\\': 
            case '"' : 
            case '$' : 
            case '/' : outIt++ = '\\';
            default  : outIt++ = *it;
        }

    return outIt;
}

static std::string escapeSomeChars(const std::string& input)
{
    std::ostringstream os;
    escapeSomeChars(input.begin(), input.end(), std::ostream_iterator<char>(os));
    return os.str();
}

namespace /*anon*/ {
    struct rawchar {   // helper - see e.g. http://bytes.com/topic/c/answers/436124-copy-istream_iterator-question
        char _c; rawchar(char c=0) : _c(c) {} 
        operator const char&() const { return _c; }
        friend std::istream& operator>>(std::istream& is, rawchar& out) { return is.get(out._c); }
    };
}

int main()
{
    static const char data[] = "\"I will \\$one day \\have \\all \\\\my slash\\es escaped, much \\like\\ in the source!\n\"";

    // use the overload for std::string
    std::cout << escapeSomeChars(data);
    std::cout << std::endl;

    // streaming in & out:
    std::istringstream is(data);
    escapeSomeChars(std::istream_iterator<rawchar>(is), std::istream_iterator<rawchar>(), std::ostream_iterator<char>(std::cout));
    std::cout << std::endl;

    // but you don't need an istream, you can use any STL iterator range
    escapeSomeChars(data, data+sizeof(data)/sizeof(data[0]), std::ostream_iterator<char>(std::cout));
    std::cout << std::endl;

    // but any source and target will do:
    std::string asstring(data);
    std::set<char> chars(asstring.begin(), asstring.end());

    asstring.clear();
    escapeSomeChars(chars.begin(), chars.end(), std::back_inserter(asstring));

    std::cout << "Unique characters in data: '" << asstring << "', but properly escaped!" << std::endl;
    return 0;
}