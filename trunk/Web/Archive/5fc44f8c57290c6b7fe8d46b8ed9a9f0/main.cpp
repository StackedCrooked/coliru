#include <iostream>
#include <string>
#include <boost/algorithm/string/replace.hpp>


struct Transcoder
{
    Transcoder(const std::string & sep, const std::string & esc) :
        sep(sep),
        esc(esc)
    {
    }

    std::string sep, esc;
};


struct Escape : Transcoder
{
    Escape(const std::string & sep, const std::string & esc) : Transcoder(sep, esc) {}

    std::string operator()(std::string s) const
    {
        using boost::algorithm::replace_all;
        replace_all(s, esc, esc + esc);
        replace_all(s, sep, esc + sep);
        return s;
    }
};


struct Unescape : Transcoder
{
    Unescape(const std::string & sep, const std::string & esc) : Transcoder(sep, esc) {}

    std::string operator()(std::string s) const
    {
        using boost::algorithm::replace_all;
        replace_all(s, esc + sep, sep);
        replace_all(s, esc + esc, esc);
        return s;
    }
};


struct Join
{
    Join(const std::string & sep, const std::string & esc) : sep(sep), esc(esc) {}

    std::string operator()(const std::string & left, const std::string & right) const
    {
        Escape escape(sep, esc);
        return escape(left) + esc + escape(right);
    }

    std::string sep, esc;
};


int main()
{
    auto sep = "&";
    auto esc = "\\";
    Join join(sep, esc);
    Escape escape(sep, esc);
    Unescape unescape(sep, esc);
    
    auto encoded = join(escape("a == b && c == d"), escape("&a = &b"));
    std::cout << "Encoded: " << encoded << std::endl;
}