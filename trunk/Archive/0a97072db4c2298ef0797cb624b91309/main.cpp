#include <boost/variant.hpp>

struct Plain
{
    std::string compress(const std::string & in) const { return in; }
};

struct Zip
{
    std::string compress(const std::string & in) const { return in; }
};


struct Visitor : boost::static_visitor<>
{
    Visitor(const std::string & s, std::string * o) : s(s), out(o) {}
    
    template<typename C>
    void operator()(C & c) const
    {
        *out = c.compress(s);
    }
    
    std::string s;
    mutable std::string * out;
};

struct Archiver
{
    void archive(const std::string & s)
    {
        std::string c;
        boost::apply_visitor(Visitor(s, &c), compressor);
    }
    
    boost::variant<Plain, Zip> compressor;
};

int main()
{
    Archiver arch;
    arch.archive("abc");
}