
#include <sstream>
#include <iostream>

template<typename Stream, typename First>
void ToStream(Stream& ss, First&& v)
{
    ss << std::forward<First>(v);
}

template<typename Stream, typename First, typename ...Rest>
void ToStream(Stream& ss, First&& first, Rest&& ...rest)
{
    ToStream(ss, first);
    ToStream(ss, std::forward<Rest>(rest)...);
}

template<typename ...Args>
std::string ToString(Args&& ...args)
{
    std::stringstream ss;
    ToStream(ss, std::forward<Args>(args)...);
    return ss.str();
}

template<typename ...Args>
std::string ToString()
{
    return std::string();
}

int main()
{
    std::cout << ToString() << std::endl;
    
    std::cout << ToString(
            "signed char(65)", ":", (signed char)(65), "\n",
            "signed short(97)", ":", (signed short)(97), "\n",
            "signed int(97)", ":", (signed int)(97), "\n",
            "signed long(97)", ":", (signed long)(97), "\n",
            "signed long long(97)", ":", (signed long long)(97), "\n",
            "unsigned char(65)", ":", (unsigned char)(65), "\n",
            "unsigned short(97)", ":", (unsigned short)(97), "\n",
            "unsigned int(97)", ":", (unsigned int)(97), "\n",
            "unsigned long(97)", ":", (unsigned long)(97), "\n",
            "unsigned long long(97)", ":", (unsigned long long)(97), "\n",
            "float(97.0)", ":", float(97), "\n",
            "double(97.0)", ":", double(97), "\n",
            "long double(97.0)", ":", (long double)(97), "\n",
            "char16_t(97.0)", ":", char16_t(97), "\n",
            "char32_t(97.0)", ":", char32_t(97), "\n",
            "std::string(\"97\")", ":", std::string("97"), "\n"
    );
}
