#include <string>
#include <set>
#include <typeinfo>
#include <sstream>
#include <cassert>
#include <iostream>
#include <map>

namespace detail 
{
    constexpr int _max(int x, int y)
    {
        return (x < y) ? y : x; 
    }

    template<typename... Args> 
        constexpr int _max(int x, int y, Args... args) 
        { 
            return _max(_max(x,y), args...);
        }
}

enum ParamDetail_INT {
    DECIMAL,
    HEX,
    OCT,
    LONG,
    ULONG,
    SIZET,
    PARAM_DETAIL_INT_LAST,
};

constexpr static const char * _parse_formats[][detail::_max(PARAM_DETAIL_INT_LAST,0)] = {
    /* Ints   */ {"%d", "%x", "%o", "%ld", "%lu", "%zu"},
    /* Floats */ {"%f"}, 
};

enum ParamTag {
    INT,
    FLOAT,
    ENUM,
    LIST,
    PARAM_LAST,
};


template<typename T, ParamTag P, int FormatSpec=0>
static T IntegralFromString(std::string const & str, T _default)
{
    T ret;
    if (std::sscanf(str.c_str(), _parse_formats[P][FormatSpec], &ret) == -1)
        return _default;
    return ret;
}

struct Policy 
{
    ParamTag tag;
    Policy(ParamTag _t) : tag(_t) { }
    virtual ~Policy() { };
    virtual bool isValid(std::string) = 0;
};


template<typename Derived>
struct ParamPolicy : public Policy
{
    ParamPolicy(ParamTag _t) : 
        Policy(_t)
    { }

    virtual bool isValid(std::string const &value)
    {
        static_cast<Derived *>(this)->isValid(value);
    }
};


template<typename T, ParamTag P, int FormatSpec>
struct IntegralPolicy : public ParamPolicy<T>
{

    IntegralPolicy(T min, T max) :
        ParamPolicy<T>(P)
    {
        mMin = min;
        mMax = max;
    }

    bool isValid(std::string const &value)
    {
        T def = -1;
        T  _ret = IntegralFromString<T, P, FormatSpec>(value, def);
        return _ret != def ? _ret <= mMax && _ret >= mMin : false ;
    }

    T mMin;
    T mMax;
};

struct EnumPolicy : public ParamPolicy<EnumPolicy>
{
    EnumPolicy(std::set<std::string> values) :
        ParamPolicy(ENUM),
        mValues(std::move(values))
    { }

    bool isValid(std::string value) 
    {
        bool _ret = mValues.find(value) != mValues.end();
        return _ret;
    }

    std::set<std::string> mValues;
};


int main(void)
{
    IntegralPolicy<int, INT, DECIMAL> ZeroToTen(0,10);
    
    std::map<std::string, std::pair<std::string, Policy *>> MAP = 
    { 
        { "hello" , { "100", &ZeroToTen } },
    };


    for (auto & p : MAP)
    {
        auto & val = std::get<1>(p);        // key
        auto & num = std::get<0>(val);      // value
        auto & comp = std::get<1>(val);     // comp
    
        //std::cout << comp->isValid(num) << std::endl;
    }
}
