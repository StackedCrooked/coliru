#include <boost/variant.hpp>

struct Plain
{
    std::string compress(const std::string & s) const { return s; }
};

struct Zip
{
    std::string compress(const std::string & s) const { return s; }
};


struct CompressorVisitor : boost::static_visitor<>
{
    CompressorVisitor(const std::string & s) : s(s) {}
    
    template<typename C>
    std::string operator()(C & c) const
    {
        return c.compress(s);
    }
    
    std::string s;
};

struct Archiver
{
    void archive(const std::string & s)
    {
        boost::apply_visitor(CompressorVisitor(s), compressor);
    }
    
    boost::variant<Plain, Zip> compressor;
};

int main()
{
    Archiver arch;
    arch.archive("abc");
}