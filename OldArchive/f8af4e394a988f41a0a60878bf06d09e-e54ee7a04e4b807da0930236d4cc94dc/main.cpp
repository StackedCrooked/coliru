#include <iostream>
#include <sstream>

struct Info
{
    template<typename T>
    Info& write(const T&)
    {
        // ... 
        return *this;
    }
};

template<typename T>
Info& operator<<(const Info& info, const T& t)
{
    return const_cast<Info&>(info).write(t);
}

int main()
{
    Info() << "hello";
}