#include <string>
#include <algorithm>
#include <sstream>
#include <cctype>
#include <unordered_map>
#include <vector>

#include <iostream>

#define stringized_enum(name, ...) \
    enum class name { __VA_ARGS__ }; \
    name name ## _value(const std::string & arg) \
    { \
        static const auto mapping = [&]() { \
            std::string str{ #__VA_ARGS__ }; \
            str.erase(std::remove_if(str.begin(), str.end(), [](auto arg){ return std::isspace(arg); }), str.end()); \
            std::istringstream stream{ std::move(str) }; \
            name val{}; \
            std::string buffer; \
            std::unordered_map<std::string, name> map; \
            while (std::getline(stream, buffer, ',')) \
            { \
                map[buffer] = static_cast<name>(static_cast<std::underlying_type_t<name>>(val)); \
                val = static_cast<name>(static_cast<std::underlying_type_t<name>>(val) + 1); \
            } \
            return map; \
        }(); \
        return mapping.at(arg); \
    } \
    \
    std::string name ## _string(name value) \
    { \
        static const auto mapping = [&]() { \
            std::string str{ #__VA_ARGS__ }; \
            str.erase(std::remove_if(str.begin(), str.end(), [](auto arg){ return std::isspace(arg); }), str.end()); \
            std::istringstream stream{ std::move(str) }; \
            name val{}; \
            std::string buffer; \
            std::vector<std::string> map; \
            while (std::getline(stream, buffer, ',')) \
            { \
                map.push_back(buffer); \
                val = static_cast<name>(static_cast<std::underlying_type_t<name>>(val) + 1); \
            } \
            return map; \
        }(); \
        return mapping.at(static_cast<std::underlying_type_t<name>>(value)); \
    }        

stringized_enum(foo,
    bar,
    baz,
    buzz
);

#include <cassert>

int main()
{
    assert(foo::buzz == foo_value("buzz"));
    assert(foo_string(foo::bar) == "bar");
}
