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
Info& operator<<(Info& info, const T& t)
{
    return info.write(t);
}

int main()
{
    Info() << "hello";
}