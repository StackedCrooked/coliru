#include <boost/variant.hpp>
#include <iostream>
#include <string>



struct JSON
{
    std::string format(const std::string& s) const
    {
        return "JSON: " + s;
    }
};


struct XML
{
    std::string format(const std::string& s) const
    {
        return "XML: " + s;
    }
};


typedef boost::variant<XML, JSON> Formatter;


struct FormatterVisitor : boost::static_visitor<std::string>
{
    FormatterVisitor(std::string s) : s(std::move(s)) {}
    
    template<typename FormatterType>
    std::string operator()(FormatterType& formatter) const
    {
        return formatter.format(s);
    }                
    
    std::string s;
};


struct Config
{   
    template<typename Formatter>
    Config(Formatter&& formatter) : mFormatter(std::forward<Formatter>(formatter)) {}
    
    std::string format(std::string s)
    {    
        return boost::apply_visitor(FormatterVisitor(s), mFormatter);
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

