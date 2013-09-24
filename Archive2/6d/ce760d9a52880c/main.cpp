#include <map>
#include <string>
#include <typeindex>

struct myClass { virtual ~myClass() {} };
struct subclass1 : myClass {};
struct subclass2 : myClass {};

#include <iostream>

int main()
{
    std::map<std::type_index, std::string> m { { typeid(myClass), "zero" }
        , { typeid(subclass1), "one" }
        , { typeid(subclass2), "two" }
    };

    myClass base;
    subclass1 s1;
    subclass2 s2;

    std::cout << m[typeid(base)] << "\n";
    std::cout << m[typeid(s1)]   << "\n";
    std::cout << m[typeid(s2)]   << "\n";

    myClass* d    = new subclass2;
    std::cout << m[typeid(*d)]   << "\n";

    delete d;
}
