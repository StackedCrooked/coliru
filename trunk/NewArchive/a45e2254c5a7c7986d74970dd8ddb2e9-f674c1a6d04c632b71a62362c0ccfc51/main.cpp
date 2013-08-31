#include <functional>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>


struct GET {};
struct POST {};
struct PUT {};

struct none {};
struct text {};
struct json {};
struct xml {};
struct html {};


template<typename Method, typename ContentType>
void handle(Method, ContentType)
{
    std::cout << "No route for " << __PRETTY_FUNCTION__ << std::endl;
}

void handle(GET, json)
{
    std::cout << "Handle (GET, json)\n";
}

void handle(POST, text)
{
    std::cout << "Handle (POST, text)\n";
}

void handle(POST, json)
{
    std::cout << "Handle (POST, json)\n";
}

template<typename Method>
void parse2(Method method, const std::string& content_type)
{
    std::map<std::string, std::function<void()>> mapping = {
        { "text",  [=] { handle(method, text{}); } },
        { "json",  [=] { handle(method, json{}); } }
    };
    
    #define MAP_CONTENT_TYPE(Name) \
        mapping.insert(std::make_pair(#Name, [=] { handle(method, Name{}); }));
        
    MAP_CONTENT_TYPE(json)
    MAP_CONTENT_TYPE(text)
    MAP_CONTENT_TYPE(html)
    MAP_CONTENT_TYPE(xml)
    
    auto it = mapping.find(content_type);
    if (it == mapping.end())
    {
        std::cerr << "Unsupported content type: " << content_type << std::endl;
        return;
    }
    
    it->second();
}

void parse1(const std::string& method, const std::string& content_type)
{
    if (method == "GET")
    {
        parse2(GET{}, content_type);
    }
    else if (method == "POST")
    {
        parse2(POST{}, content_type);
    }
    else if (method == "PUT")
    {
        parse2(PUT{}, content_type);
    }
    else
    {
        std::cerr << "Unsupported method: " << method << std::endl;
    }
}


void test()
{
    parse1("GET", "json");
    parse1("GET", "xml");
    parse1("GET", "text");
    parse1("POST", "json");
    parse1("POST", "xml");
    parse1("POST", "text");
}

int main()
{
    try
    {
        test();
    }
    catch (const std::exception& exc)
    {
        std::cout << exc.what() << std::endl;
    }
}