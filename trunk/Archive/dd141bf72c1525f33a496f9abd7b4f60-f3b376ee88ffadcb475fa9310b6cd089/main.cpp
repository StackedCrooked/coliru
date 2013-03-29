#include <iostream>
#include <sstream>


enum LogLevel 
{
    Trace,
    Info,
    Warning,
    Error
};


bool is_allowed(LogLevel level)
{
    return level >= Info;
}


struct LogItem
{
    LogItem() : os(std::cout) {}
    
    std::ostream & os;
};

#define LOG(level) \
    if (!is_allowed(level)) ; else LogItem().os

int main()
{
    LOG(LOG_LEVEL) << "Just a test.";
}


