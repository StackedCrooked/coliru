#include <map>
#include <iostream>
#include <string>
#include <boost/foreach.hpp>
#include <sstream>
#include <cstdarg>

enum JType {
    JInt = 0,
    JVoid = 1,
    JString = 2,
    JBool = 3
};

std::string JTypeToString(JType type)
{
    switch (type)
    {
        case(JInt): return "I";
        case(JVoid): return "V";
        case(JString): return "Ljava/lang/String;";
        case(JBool): return "Z";
        default: return "";
    }
    return "";
}

template<int N>
struct JTypeList;

template<>
struct JTypeList<0>
{
    void insert(std::stringstream& ss) const {}
};

template<>
struct JTypeList<1> : JTypeList<0>
{
    JTypeList(JType v) : value(v) {};
    
    JTypeList(JTypeList<0> const&, JType v)
        : value(v) {}
        
    void insert(std::stringstream& ss) const
    {
        ss << JTypeToString(value);
    }
        
    JType value;
};

template<int N>
struct JTypeList : JTypeList<N-1>
{
    JTypeList(JTypeList<N-1> const& init, JType last)
        : JTypeList<N-1>(init, init.value), value(last) {}

    void insert(std::stringstream& ss) const
    {
        JTypeList<N-1>::insert(ss);
        ss << JTypeToString(value);
    }

    JType value;
};

JTypeList<2> operator,(JType lhs, JType rhs)
{
    return JTypeList<2>(JTypeList<1>(lhs), rhs);
}

template<int N>
JTypeList<N+1> operator,(JTypeList<N> const& l, JType next)
{
    return JTypeList<N+1>(l, next);
}

static JTypeList<0> const NoArgs = {};

template<int N>
std::string MakeSig(JType returnType, JTypeList<N> const& args)
{
    std::stringstream ss;
    ss << "(";
    args.insert(ss);
    ss << ")" << JTypeToString(returnType);
    return ss.str();
}

struct Sig
{
    Sig(JType r) : returnType(r) {}
    
    template<int N>
    std::string operator[](JTypeList<N> const& l) const
    {
        return MakeSig(returnType, l);
    }
    
    JType returnType;
};

int main()
{
    std::cout << MakeSig(JInt, (JString, JBool)) << "\n";
    std::cout << MakeSig(JInt, NoArgs) << "\n";
    std::cout << Sig(JBool)[JInt, JInt, JString] << "\n";
}