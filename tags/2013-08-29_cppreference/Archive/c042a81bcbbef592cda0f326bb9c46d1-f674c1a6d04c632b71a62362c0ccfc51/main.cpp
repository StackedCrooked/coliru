#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>


struct GET {};
struct POST {};

struct none {};
struct text {};
struct json {};


template<typename Method, typename ContentType>
void handle(Method, ContentType)
{
    std::cerr << "No route for " << __PRETTY_FUNCTION__ << std::endl;
}


void handle(GET, none)
{
    std::cerr << "Handle " << __PRETTY_FUNCTION__ << std::endl;
}


void handle(POST, text)
{
    std::cerr << "Handle " << __PRETTY_FUNCTION__ << std::endl;
}


void handle(POST, json)
{
    std::cerr << "Handle " << __PRETTY_FUNCTION__ << std::endl;
}

template<typename Method>
void parse2(Method method, const std::string& content_type)
{
//    typedef void(*Function)();
//    std::map<std::string, Function> mapping;
//    mapping.insert(std::make_pair("text", [=]{ handle(method, text{}); }));
//    mapping.insert(std::make_pair("json", [=]{ handle(method, json{}); }));
    
    if (content_type.empty())
    {
        handle(method, none{});
    }
    else if (content_type == "text")
    {
        handle(method, text{});
    }
    else if (content_type == "json")
    {
        handle(method, json{});
    }
    else
    {
        throw std::runtime_error("Unsupported content type.");
    }
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
    else
    {
        throw std::runtime_error("Unsupported method.");
    }
}


int main()
{
    parse1("GET", "json");
    parse1("GET", "");
    parse1("POST", "json");
    parse1("POST", "text");
}