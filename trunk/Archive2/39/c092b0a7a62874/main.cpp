#include <set>
#include <cassert>
#include <iostream>
#include <vector>

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

// ************************** CRTP

struct Policy 
{
    ParamTag tag;
    Policy(ParamTag _t) : tag(_t) { }
    virtual ~Policy() { };
};


template<typename Derived>
struct ParamPolicy : public Policy
{
    ParamPolicy(ParamTag _t) : 
        Policy(_t)
    { }

    bool isValid(std::string const &value)
    {
        return static_cast<Derived *>(this)->isVald(value);
    }
};


template<typename T, ParamTag P, int FormatSpec>
struct IntegralPolicy : public ParamPolicy<T>
{

    IntegralPolicy(T min, T max) :
        ParamPolicy<T>(P)
    {
        //assert(min <= max);
        //assert(min - 1 == max);
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
    IntegralPolicy<int, INT, DECIMAL> i(0,101);
    EnumPolicy e{{"hello", "world"}};

    std::cout << "i: (" << i.mMin << "," << i.mMax << "): " << i.isValid("101") << std::endl;
    std::cout << "e: "  << e.isValid("hello") << std::endl;

    
    std::vector<Policy *> p { &i, &e };

    //for (auto & e: p) {
    //    
    //    switch(e->tag) 
    //    {
    //        case INT: 
    //            std::cout << "INT" << std::endl;
    //            static_cast<IntegralPolicy *>(e)->isValid("100") ;break;        
    //        default: break;
    //    };
    //         

    //}


}
