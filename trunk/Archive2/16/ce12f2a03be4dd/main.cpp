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

std::string MakeSig(JType returnType, int argCount, ...)
{
    std::stringstream ss;
    ss << "(";
    va_list args;
    va_start(args, argCount);
    for (int i = 0; i < argCount; ++i)
    {
        JType arg = (JType)va_arg(args, int);
        ss << JTypeToString(arg);
    }
    va_end(args);
    ss << ")" << JTypeToString(returnType);
    return ss.str();
}

int main()
{
    std::cout << MakeSig(JType::JInt, 2, JType::JString, JType::JBool);
}