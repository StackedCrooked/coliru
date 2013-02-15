#include "boost/variant.hpp"
#include <iostream>
#include <string>


namespace compression {

template<class T> struct PolicyInterface
{
    void operator()(std::ostream & os, const std::string & s) const
    {
        static_cast<const T&>(*this).invoke(os, s);
    }
};

struct Plain : PolicyInterface<Plain>
{
    void invoke(std::ostream & os, const std::string & s) const
    {
        os << s;
    }
};

struct WithStars : PolicyInterface<WithStars>
{
    void invoke(std::ostream & os, const std::string & s) const
    {
        os << "*** " << s << " ***";
    }
};


typedef boost::variant<WithStars, Plain> policy;


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

template<typename ...Args>
void visit(const policy & p, Args && ...args)
{
    PolicyVisitor v(std::forward<Args>(args)...);
    p.apply_visitor(v);
}

} // namespace compression


struct Archive
{
    template<typename Compressor>
    Archive(const Compressor & c) : compressor(c)
    {
    }
    
    void archive(std::ostream & os, const std::string & s)
    {
        compression::PolicyVisitor v{os, s};
        //compressor.apply_visitor(v);
        visit(compressor, os, s);
    }
    
    mutable compression::policy compressor;
};


int main()
{
    Archive arch{compression::WithStars{}};
    arch.archive(std::cout, "some text");
    std::cout << std::endl;
    
    Archive arch2{compression::Plain{}};
    arch2.archive(std::cout, "some text");
}