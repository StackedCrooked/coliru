#include <iostream>

class Log
{
public:    
    enum logModifiers
    {
            lol,
            wat
    };

    template<class T> const Log& operator<<(const T& t) const {
            return *this;
    }
};
 
const Log& Log::operator<< <Log::logModifiers>(const Log::logModifiers& t) const;
 
const Log& Log::operator<< <Log::logModifiers> (const Log::logModifiers& t) const 
{
    //specialized cosax
}

int main(int argc, char *argv[])
{
    Log log;
    log << (Log::logModifiers) Log::lol;
}