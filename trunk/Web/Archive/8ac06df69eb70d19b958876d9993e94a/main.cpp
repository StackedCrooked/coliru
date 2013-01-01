#include "boost/variant.hpp"
#include <iostream>
#include <string>

namespace policies {

template<class T> struct PolicyInterface
{
    void operator()(std::ostream & os, const std::string & s) const
    {
        static_cast<const T&>(*this).invoke(os, s);
    }
};

struct PolicyVisitor : boost::static_visitor<>
{
    PolicyVisitor(std::ostream & os, const std::string & s) : os(os), s(s) {}

    template<typename C>
    void operator()(const PolicyInterface<C> & c) const
    {
        c(os, s);
    }
    
    std::ostream & os;
    const std::string & s;
};

template<typename P, typename ...Args>
void apply(const P & p, Args && ...args)
{
    PolicyVisitor v(std::forward<Args>(args)...);
    p.apply_visitor(v);
}


} // namespace policies


namespace policies {
namespace compression {


struct Plain : PolicyInterface<Plain>
{
    void invoke(std::ostream & os, const std::string & s) const
    {
        os << "plain[" << s << "]";
    }
};


struct Zip : PolicyInterface<Zip>
{
    void invoke(std::ostream & os, const std::string & s) const
    {
        os << "zip[" << s << "]";
    }
};


typedef boost::variant<Plain, Zip> Policy;


} } // namespace policies::compression


class Archive
{
    typedef policies::compression::Policy CompressionPolicy;
    mutable CompressionPolicy compressor;
    
public:
    template<typename Compressor>
    Archive(const Compressor & c) : compressor(c)
    {
    }
    
    void archive(std::ostream & os, const std::string & s)
    {
        apply(compressor, os, s);
    }    
};


int main()
{
    using policies::compression::Zip;
    using policies::compression::Plain;
    
    Archive zip_archive(Zip{});
    zip_archive.archive(std::cout, "ziptest");
    
    std::cout << std::endl;
    
    Archive plain_archive(Plain{});
    plain_archive.archive(std::cout, "plaintest");
}

