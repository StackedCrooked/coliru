#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include <numeric>
#include <sstream>

template<typename T>
std::string slow_to_string(T val)
{
    std::stringstream ss;
    ss << std::boolalpha << val;
    return ss.str();
}

void replace_all(std::string& str, const std::string& from, const std::string& to)
{
    if(from.empty())
        return;
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos)
    {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}

template<typename T>
void replace_str(std::string& str, int arg, T val)
{
    replace_all(str, "%" + std::to_string(arg), slow_to_string(val));
}

// -----------------------------------
template<typename S>
void log_impl(S& str, int arg)
{
}

template<typename S, typename T, typename... Args>
void log_impl(S& str, int arg, T arg0, Args... args)
{
    str(arg, arg0);
    log_impl(str, arg+1, args...);
}

// -----------------------------------
struct StringStream
{
    std::string str;

    template<typename T>
    void operator()(int n, T val)
    {
        replace_str(str, n, val);
    }
};

// -----------------------------------
void log(const char* format)
{
    std::cout << format << "\n";
}

template<typename T, typename... Args>
void log(const char* format, T arg0, Args... args)
{
    StringStream ss;
    ss.str = format;
    log_impl(ss, 1, arg0, args...);
    std::cout << ss.str << "\n";
}

int main ()
{
    std::cout << "Test 1:\n";
    log("format: %1 - %3 - %2");

    std::cout << "Test 2:\n";
    log("format: %1 - %3 - %2", 5);

    std::cout << "Test 3:\n";
    log("format: %1 - %3 - %2", "abs", 30);

    std::cout << "Test 4:\n";
    log("format: %1 - %3 - %2", 1465.5, std::string("std::string"), true);

    std::cout << "Test 5:\n";
    log("format: %1 - %3 - %2", false, "AAA", 3.14f, 123);
}
