// http://stackoverflow.com/questions/26784238/how-to-implement-parent-class-with-templated-function-in-c
#include <iostream>

namespace json {
    struct Object {};
}

class IParser
{
public:
    template <typename T> 
    json::Object Parse(const T&, json::Object&);
};

template<>
json::Object IParser::Parse<std::string>( const std::string & str, json::Object &obj ) {
    return obj;
}

class HTMLParser : public IParser
{
public:
    HTMLParser();
    ~HTMLParser();

    json::Object Parse(std::string const&, json::Object&);
};

HTMLParser::HTMLParser()
{
    std::cout << "constructed" << std::endl;
}

HTMLParser::~HTMLParser()
{
    std::cout << "destructed" << std::endl;
}

json::Object HTMLParser::Parse(std::string const& data, json::Object& object)
{
    // do something
    return json::Object();
}


int main()
{
    IParser* parser = new HTMLParser();
    json::Object obj;
    std::string str("<body></body>");
    parser->Parse(str,obj);
    return 0;
}