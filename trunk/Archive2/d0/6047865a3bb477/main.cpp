#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <memory>
#include <chrono>
#include <string>
#include <algorithm>
#include <cassert>
#include <type_traits>




class ObjectBuilder
{
public:
    template<typename T, typename... Args>
    static std::shared_ptr<T> make_object(Args&&... args)
    {
        struct Access : public T {
            Access(Args&&... args) :
                T(std::forward<Args>(args)...) {
                // empty
            }
        };

        // call T's constructor
        std::shared_ptr<T> ob =
                std::make_shared<Access>(
                    std::forward<Args>(args)...);

        return ob;
    }
};



template<typename T, typename... Args>
static std::shared_ptr<T> make_object(Args&&...args)
{
    return ObjectBuilder::make_object<T>(std::forward<Args>(args)...);
}



class Object : public std::enable_shared_from_this<Object>
{
    friend class ObjectBuilder;

public:
    virtual ~Object() {}

    std::type_info const & GetTypeInfo()
    {
        return typeid(*this);
    }

protected:
    Object() {}
};



#include <cxxabi.h>
std::string demangle(const char* name) {

    int status = -4; // some arbitrary value to eliminate the compiler warning

    // enable c++11 by passing the flag -std=c++11 to g++
    std::unique_ptr<char, void(*)(void*)> res {
        abi::__cxa_demangle(name, NULL, NULL, &status),
        std::free
    };

    return (status==0) ? res.get() : name ;
}



int main()
{
    std::shared_ptr<Object> obj = make_object<Object>();
    std::cout << demangle(obj->GetTypeInfo().name()) << std::endl;

    return 0;
}