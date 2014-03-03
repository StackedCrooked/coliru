#include <iostream>

class Log
{
public:    
    enum logModifiers
    {
            lol,
            wat
    };
};
 
template<class T> const Log& operator<<(const Log& l, const T& t) {
    return l;
} 

const Log& operator<<(const Log& l, const Log::logModifiers& t)
{
    std::cout << "Hello" << std::endl;
    return l;
}

int main(int argc, char *argv[])
{
    Log log;
    log << Log::lol;
}