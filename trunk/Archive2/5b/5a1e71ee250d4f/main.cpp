#include <map>
#include <iostream>
#include <string>
#include <boost/foreach.hpp>
#include <sstream>
#include <cstdarg>

enum JTypeKind
{
    JInt,
    JVoid,
    JString,
    JBool,
	JLong,
};

enum JTypeFlag {
    IsArray = (1 << 0)
};

struct JType {
    JType(JTypeKind kind, std::initializer_list<JTypeFlag> flags = {}) : kind(kind), flags(0) {
        for (unsigned flag : flags) {
            this->flags |= flag;
        }
    }

    std::string ToString() {
        std::string result = "";
        
        if (flags & IsArray) {
            result += "[";
        }
        
        switch (kind)
        {
            case(JInt): result += "I"; break;
            case(JVoid): result += "V"; break;
            case(JString): result += "Ljava/lang/String;"; break;
            case(JBool): result += "Z"; break;
            case(JLong): result += "J"; break;
        }
        
        return result;
    };
    
    JTypeKind kind;
    unsigned flags;
};

std::string MakeSig(JType returnType, std::initializer_list<JType> args)
{
    std::stringstream ss;
    ss << "(";
    for (auto arg : args)
    {
        ss << arg.ToString();
    }
    ss << ")" << returnType.ToString();
    return ss.str();
}

int main()
{
    JType t(JInt);
    JType t2(JInt, { IsArray });
    std::cout << MakeSig(t, { t2 });
}