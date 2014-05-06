#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdarg.h>
#include <cstdio>

void write(char const *severity, char const *filename, char const *function, std::size_t lineno, char const *format, ...)
{
     va_list ap;
     va_start (ap, format);
     std::cout << std::string(50, '-') << "\n";
     std::cout << severity << ": ";
     std::vprintf(format, ap); 
     va_end (ap);
     std::cout << "\n" << filename << "(" << lineno << "): " << function << std::endl;
}

#define INFO(...)       write("INFORMATION", __FILE__, __PRETTY_FUNCTION__, __LINE__, __VA_ARGS__)
#define WARNING(...)    write("WARNING", __FILE__, __PRETTY_FUNCTION__, __LINE__, __VA_ARGS__)
#define ERROR(...)      write("ERROR", __FILE__, __PRETTY_FUNCTION__, __LINE__, __VA_ARGS__)
#define VERBOSE(...)    write("VERBOSE", __FILE__, __PRETTY_FUNCTION__, __LINE__, __VA_ARGS__)

int main()
{
    int salary = 0;
    INFO("Well, computing our salary, and it turns out to be %d", salary);
    ERROR("Cannot be divided by zero");
}


