#include <map>
#include <iostream>
#include <string>
#include <boost/foreach.hpp>
#include <sstream>
#include <cstdarg>

enum JType 
{
        JInt = 0,
        JVoid = 1,
        JString = 2,
        JBool = 4,
		JLong = 8,
        JArray = 16
};

JType operator| (JType lhs, JType rhs)
{
    return (JType)((int)lhs | (int)rhs);
}

bool IsArray(JType type)
{
    return (type | JArray) == type;
}

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

std::string MakeSig(JType returnType, std::initializer_list<JType> args)
{
    std::stringstream ss;
    ss << "(";
    for (auto arg : args)
    {
        ss << JTypeToString(arg);
    }
    ss << ")" << JTypeToString(returnType);
    return ss.str();
}

int main()
{
    JType t = JInt;
    JType t2 = JArray | JInt;
    std::cout << IsArray(t) << " " << IsArray(t2);
}