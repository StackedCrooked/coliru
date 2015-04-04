#include <string>
#include <algorithm>
#include <sstream>
#include <cctype>
#include <unordered_map>
#include <vector>

#include <iostream>

namespace reaver { inline namespace _v1
{
    template<typename Enum>
    const std::vector<Enum> & enum_values();

    namespace _detail
    {
        template<typename Enum, typename Context>
        struct _enum_wrapper
        {
            static Enum next;

            _enum_wrapper() : value{ next }
            {
                next = static_cast<Enum>(static_cast<std::underlying_type_t<Enum>>(next) + 1);
            }

            _enum_wrapper(std::underlying_type_t<Enum> current) : _enum_wrapper{ static_cast<Enum>(current) }
            {
            }

            _enum_wrapper(Enum current) : value{ current }
            {
                next = static_cast<Enum>(static_cast<std::underlying_type_t<Enum>>(current) + 1);
            }

            operator Enum() const
            {
                return value;
            }

            template<typename T>
            _enum_wrapper & operator=(T)
            {
                return *this;
            }

            Enum value;
        };

        template<typename Enum, typename Context>
        Enum _enum_wrapper<Enum, Context>::next = {};
    }
}}

#define reflected_enum(name, ...) \
    template<typename T> T from_string(const std::string &); \
    enum class name { __VA_ARGS__ }; \
    \
    template<> \
    const std::vector<name> & ::reaver::enum_values<name>() \
    { \
        static auto values = []{ \
            ::reaver::_detail::_enum_wrapper<name, class context> __VA_ARGS__; \
            std::vector<name> vec{ __VA_ARGS__ }; \
            return vec; \
        }(); \
        return values; \
    } \
    \
    template<> \
    name from_string<name>(const std::string & arg) \
    { \
        static const auto mapping = [&]() { \
            std::string str{ #__VA_ARGS__ }; \
            str.erase(std::remove_if(str.begin(), str.end(), [](auto arg){ return std::isspace(arg); }), str.end()); \
            std::istringstream stream{ std::move(str) }; \
            \
            auto it = ::reaver::enum_values<name>().begin(); \
            \
            std::string buffer; \
            std::unordered_map<std::string, name> map; \
            while (std::getline(stream, buffer, ',')) \
            { \
                map.emplace(buffer, *it++); \
            } \
            return map; \
        }(); \
        return mapping.at(arg); \
    } \
    \
    std::string to_string(name value) \
    { \
        static const auto mapping = [&]() { \
            std::string str{ #__VA_ARGS__ }; \
            str.erase(std::remove_if(str.begin(), str.end(), [](auto arg){ return std::isspace(arg); }), str.end()); \
            std::istringstream stream{ std::move(str) }; \
            \
            auto it = ::reaver::enum_values<name>().begin(); \
            \
            std::string buffer; \
            std::unordered_map<std::underlying_type_t<name>, std::string> map; \
            while (std::getline(stream, buffer, ',')) \
            { \
                buffer = buffer.substr(0, buffer.find('=')); \
                map.emplace(static_cast<std::underlying_type_t<name>>(*it++), buffer); \
            } \
            return map; \
        }(); \
        return mapping.at(static_cast<std::underlying_type_t<name>>(value)); \
    }

reflected_enum(foo,
    bar,
    baz = 6,
    buzz
);

#include <cassert>

int main()
{
    for (auto && elem : reaver::enum_values<foo>()) { std::cout << static_cast<std::underlying_type_t<foo>>(elem) << ", "; };
    std::cout << std::endl;
    assert(foo::buzz == from_string<foo>("buzz"));
    assert(to_string(foo::baz) == "baz");
}
