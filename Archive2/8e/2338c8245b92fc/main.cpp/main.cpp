#include <iostream>

//HPP

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
 
template<> const Log& Log::operator<< <Log::logModifiers>(const Log::logModifiers& t) const;

// CPP
template<> const Log& Log::operator<< <Log::logModifiers> (const Log::logModifiers& t) const  {
    return *this;
}

//MAIN
int main(int argc, char *argv[])
{
    Log log;
    log << Log::lol;
    std::cout << "wat" << std::endl;
}