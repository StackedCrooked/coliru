#include <iostream>

class Log
{
public:    
    enum logModifiers
    {
            lol,
            wat
    };

    template<class T> const Log& operator<<(const T& t) const;
};
 
template<class T>
const Log& Log::operator<< (const T& t) const 
{
    //normal cosax
    return *this;
}

template<>
const Log& Log::operator<<  (const Log::logModifiers& t) const 
{
    //specialized cosax
    return *this;
}

int main(int argc, char *argv[])
{
    Log log;
    log << (Log::logModifiers) Log::lol;
}