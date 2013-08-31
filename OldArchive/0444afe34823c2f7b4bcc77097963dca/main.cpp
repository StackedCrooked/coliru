#include "boost/variant.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <tuple>


namespace policies {


template<class T> struct PolicyInterface
{
    template<typename ...Args>
    void operator()(Args && ...args) const
    {
        static_cast<const T&>(*this).invoke(std::forward<Args>(args)...);
    }
};


template<typename ...Args>
struct PolicyVisitor : boost::static_visitor<>
{    
    PolicyVisitor(Args && ...args) : args_(std::make_tuple(args...)) {}

    template<typename C>
    void operator()(const PolicyInterface<C> & c) const
    {
        c(os, s);
    }
    
    std::tuple<Args...> args_;
};


template<typename P, typename ...Args>
void RunPolicy(const P & p, Args && ...args)
{
    PolicyVisitor<Args...> v(std::forward<Args>(args)...);
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


} // namespace compression


namespace serialization {


struct JSON : PolicyInterface<JSON>
{
    template<typename T>
    void invoke(std::ostream & os, const T & t) const
    {
        os << "{" << t << "}";
    }
};


struct XML : PolicyInterface<XML>
{
    template<typename T>
    void invoke(std::ostream & os, const T & t) const
    {
        os << "<" << t << ">";
    }
};


typedef boost::variant<JSON, XML> Policy;


} } // namespace policies::compression


class Archive
{
    typedef policies::serialization::Policy SerializationPolicy;
    SerializationPolicy ser;
    
    typedef policies::compression::Policy   CompressionPolicy;
    mutable CompressionPolicy comp;
    
public:
    Archive(const SerializationPolicy & s, const CompressionPolicy & c) : ser(s), comp(c)
    {
    }
    
    template<typename T>
    void archive(std::ostream & os, const T & t)
    {
        std::stringstream ss;
        RunPolicy(ser,  ss, t);
        RunPolicy(comp, os, ss.str());
    }    
};


struct Point
{
    Point(int x, int y) : x(x), y(y) {}    
    int x, y;
};


std::ostream& operator<<(std::ostream& os, Point p)
{
    return os << "(" << p.x << ", " << p.y << ")";
}


int main()
{
    using namespace policies::compression;
    using namespace policies::serialization;    

    
    Archive zip_archive(JSON{}, Zip{});
    zip_archive.archive(std::cout, Point{1, 2});
    
    std::cout << std::endl;
    
    Archive plain_archive(XML{}, Plain{});
    plain_archive.archive(std::cout, Point{3, 4});
}

