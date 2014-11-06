// http://stackoverflow.com/questions/26784238/how-to-implement-parent-class-with-templated-function-in-c
#include <iostream>
#include <string>
using std::string;

#define TEMPLATE 1

namespace json {
    struct Object {};
}

class IParser
{
public:
#if TEMPLATE
    template <typename T> 
    json::Object Parse(const T&, json::Object);
#else
    virtual json::Object Parse(const string&, json::Object&) {
        // do something
        std::cout << "Parse member function of base class IParser called\n";
        return json::Object();
    }
#endif

};

#if TEMPLATE
template<>
json::Object IParser::Parse<std::string>( const std::string & str, json::Object obj ) {
    std::cout << "Specialization for string of base class Iparser called\n";
    return obj;
}
#endif

class HTMLParser : public IParser
{
public:
    HTMLParser();
    ~HTMLParser();

    json::Object Parse(const string&, json::Object&);
};

HTMLParser::HTMLParser()
{
    std::cout << "constructed" << std::endl;
}

HTMLParser::~HTMLParser()
{
    std::cout << "destructed" << std::endl;
}

json::Object HTMLParser::Parse(const string& data, json::Object& object)
{
    // do something
    std::cout << "Parse member function of derived class HTMLParser called\n";
    return json::Object();
}


int main()
{
    HTMLParser* html_parser = new HTMLParser();
    IParser* parser = html_parser;
    json::Object obj;
    std::string str("<body></body>");
    parser->Parse(str,obj);
    html_parser->Parse(str,obj);
    return 0;
}