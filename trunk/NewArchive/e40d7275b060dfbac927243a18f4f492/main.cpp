#include "boost/variant.hpp"
#include <iostream>
#include <string>


struct Plain
{
    void compress(std::ostream & os, const std::string & s)
    {
        os << s;
    }
};


struct WithStars
{
    void compress(std::ostream & os, const std::string & s)
    {
        os << "*** " << s << " ***";
    }
};


struct Archive
{
    typedef boost::variant<WithStars, Plain> CompressionVariant;
    
    template<typename C>
    Archive(const C & c) : mCompressionVariant{c}
    {
    }
    
    void archive(std::ostream & os, const std::string & s)
    {
        struct visitor : boost::static_visitor<>
        {
            visitor(std::ostream & os, const std::string & s) : os(os), s(s) {}
    
            void operator()(Plain & c)     const { c.compress(os, s); }
            void operator()(WithStars & c) const { c.compress(os, s); }
            
            std::ostream & os;
            const std::string & s;
        };
        visitor v{os, s};
        mCompressionVariant.apply_visitor(v);
    }
    
    mutable CompressionVariant mCompressionVariant;
};


int main()
{
    Archive arch{WithStars{}};
    arch.archive(std::cout, "some text");
    std::cout << std::endl;
    
    Archive arch2{Plain{}};
    arch2.archive(std::cout, "some text");
}