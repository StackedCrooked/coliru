#include <iostream>
#include <string>
#include <set>
#include <typeinfo>

static std::set<const std::type_info*> gExceptions;


template<typename T>
struct AutoRegister
{
    AutoRegister()
    {
        static bool b = []() -> bool {
            std::cout << "Registering " << typeid(T).name() << std::endl;
            gExceptions.insert(&typeid(T));
            return true;
        }();
        (void)b;
    }
};

struct ARP
{
    // macro expansion
    struct ARPTimeout {};
    AutoRegister<ARPTimeout> mAutoRegister_ARPTimeout; // member variable which will automatically register the exception for us 
};


int main()
{
    ARP arp1;
    ARP arp2;
}