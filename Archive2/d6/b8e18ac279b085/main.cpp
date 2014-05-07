#include <iostream>
#include <memory>
#include <typeinfo>
#include <string>
#include <cxxabi.h>


 
std::string demangle(const char * name)
{
    int st;
    std::shared_ptr<char> p(abi::__cxa_demangle(name, 0, 0, &st), std::free);
    if (st != 0)
    {
        switch (st)
        {
            case -1: throw std::runtime_error("A memory allocation failure occurred.");
            case -2: throw std::runtime_error("Not a valid name under the GCC C++ ABI mangling rules.");
            case -3: throw std::runtime_error("One of the arguments is invalid.");
            default: throw std::runtime_error("Unexpected demangle status");
        }
    }
    return std::string(p.get());
}

template<typename T>
std::string get_typename_ADL(T)
{
    std::cout << "FAIL: " << demangle(typeid(T).name()) << std::endl;
    return "";
}



namespace Common
{
        
    namespace RPC
    {
        template<typename T>
        struct Identity { typedef T type; };
        
        struct Archive
        {        
            template<typename T>
            std::string serialize()
            {
                return get_typename_ADL(Identity<T>()); // ADL lookup!
            }
        };
    }
    
    namespace App
    {    
        template<typename T>
        std::string get_typename_ADL(RPC::Identity<T>)
        {
            std::cout << "ADL: " << demangle(typeid(T).name()) << std::endl;
            return demangle(typeid(T).name());
        }
        
        struct Tool {};
        
        namespace Vehicles
        {        
            struct Car : Tool {};
        }
        
        namespace Weapons
        {
            using App::get_typename_ADL;
            struct Knife : Tool {};
            struct Spear {};
        }
        
        namespace Utensils
        {
            struct Pen {};
        }
    }
}


int main()
{    
    using namespace Common;
    
    RPC::Archive archive;
    archive.serialize<App::Tool>();
    archive.serialize<App::Vehicles::Car>();
    archive.serialize<App::Weapons::Spear>();
    archive.serialize<App::Weapons::Knife>();
    archive.serialize<App::Utensils::Pen>();
}


