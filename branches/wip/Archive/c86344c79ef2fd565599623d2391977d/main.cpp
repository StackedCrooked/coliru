#include "boost/variant.hpp"
#include <iostream>
#include <string>


struct Plain { void compress(std::ostream & os, const std::string & s) { os << s << "\n";        } };
struct Zip   { void compress(std::ostream & os, const std::string & s) { os << s << "_zipped\n"; } };


struct visitor : boost::static_visitor<>
{
    visitor(std::ostream & os, std::string s) : os(os), s(s) {}
    
    template<typename C>
    void operator()(C & c) const
    {
        c.compress(os, s);
    }
    
    std::ostream & os;
    std::string s;
};


struct Archive
{
    typedef boost::variant<Zip, Plain> Compressor;
    
    template<typename C>
    Archive(const C & c) : mCompressor{c} { }
    
    void archive(std::ostream & os, const std::string & s) const
    {   
        visitor v{os, s};
        mCompressor.apply_visitor(v);
    }
    
    mutable Compressor mCompressor;
};


int main()
{
    Archive arch({Zip});
    arch.archive(std::cout, "text");
}

