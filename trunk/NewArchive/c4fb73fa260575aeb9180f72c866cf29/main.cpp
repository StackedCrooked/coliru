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

int main()
{
    
    
}