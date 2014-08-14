#include <map>
#include <cstring>
#include <iostream>
namespace MyLib {

#define DECLARE_ENUM( type ) template<> std::map<const char*, type>  \
            MyLib::Enum<type>::mMap = std::map<const char*, type>(); \
            template<> MyLib::Enum<type>::Enum (void)

template <typename Type> class Enum
{
private:
    Enum (void);

public:
    static int Size (void) { /* ... */ return 0; }

private:
    static std::map<const char*, Type> mMap;
};

}

enum MyEnum
{
    value1, value2, value3,
};

DECLARE_ENUM (MyEnum)
{
    mMap["value1"] = value1;
    mMap["value2"] = value2;
    mMap["value3"] = value3;
}

void SomeFunc (void)
{
    std::cout << MyLib::Enum<MyEnum>::Size();
}

int main() { SomeFunc(); }