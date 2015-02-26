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

class Object : public std::enable_shared_from_this<Object>
{
private:
    Object(Object const &) = delete;
    Object(Object &&) = delete;
    Object & operator = (Object const &) = delete;
    Object & operator = (Object &&) = delete;

    Object()
    {
        std::cout << "Object Created (0)" << std::endl;
    }

    Object(int)
    {
        std::cout << "Object Created (1)" << std::endl;
    }

    Object(int,int,int)
    {
        std::cout << "Object Created (3)" << std::endl;
    }

public:
    virtual ~Object()
    {
        // empty
    }

    template<typename... Args>
    static std::shared_ptr<Object> Create(Args&&... args)
    {
        struct Access : public Object {
            Access(Args&&... args) :
                Object(std::forward<Args>(args)...) {
                // empty
            }
        };

        auto ob =  std::make_shared<Access>(std::forward<Args>(args)...);
        return ob;
    }
};



int main()
{
    auto obj0 = Object::Create();
    auto obj1 = Object::Create(3);
    auto obj2 = Object::Create(0,2,3);
    return 0;
}