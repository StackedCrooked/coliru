#include <cctype>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

template <typename It>
std::string sanitize(It f, It l) { 
    std::ostringstream oss;
    for (;f!=l;++f)
    {
        if((std::isgraph(*f) || std::isspace(*f)) && *f != '\r' && *f != '\n')
            oss << *f;
        else
            oss << "%" << std::hex << std::setw(2) << std::setfill('0') << 
                static_cast<unsigned>(static_cast<unsigned char>(*f));
    }
    return oss.str();
}

template <typename C>
std::string sanitize(C const& c) { 
    using std::begin;
    using std::end;

    return sanitize(begin(c), end(c));
}

int main()
{
    std::cout << sanitize("Hello\tworld\r\n. §1.3 \b") << "\n";
}