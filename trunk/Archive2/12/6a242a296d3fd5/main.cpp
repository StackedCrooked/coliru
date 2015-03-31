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
    std::cout << MakeSig(JInt, {JString, JBool}) << std::endl;
    std::cout << MakeSig(JInt, {});
}