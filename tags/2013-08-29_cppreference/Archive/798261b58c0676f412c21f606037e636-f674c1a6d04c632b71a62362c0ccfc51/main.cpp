#include <boost/variant.hpp>
#include <iostream>
#include <string>



struct JSON
{
    std::string operator()(const std::string& s) const
    {
        return "JSON: " + s;
    }
};


struct XML
{
    std::string operator()(const std::string& s) const
    {
        return "XML: " + s;
    }
};


typedef boost::variant<XML, JSON> Formatter;


template<typename R, typename T>
struct Visitor : boost::static_visitor<R>
{    
    Visitor(T& t) : t(t) {}
    
    template<typename Element>
    R operator()(Element& element) const
    {
        return element(t);
    }
    
    T& t;
};


struct Config
{   
    template<typename Formatter>
    Config(Formatter&& formatter) : mFormatter(std::forward<Formatter>(formatter)) {}
    
    std::string format(std::string s)
    {    
        return boost::apply_visitor(Visitor<std::string, std::string>(s), mFormatter);
    }    
    
private:
    Formatter mFormatter;
};


void test(boost::variant<XML, JSON> formatter)
{
    Config config{formatter};
    std::cout << config.format("abc") << std::endl;
}



int main()
{
    test(XML{});
    test(JSON{});
}

