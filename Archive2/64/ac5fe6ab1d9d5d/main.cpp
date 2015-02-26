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

template<typename T, typename... Args>
std::shared_ptr<T> make_object(Args&&... args)
{
    // This Access class grants std::make_shared
    // access to call T's constructor which should
    // be either private or protected as I think
    // Access indirectly becomes a friend of T
    // when friendship is granted to make_object
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

    // call T::init
    ob->init();

    return ob;
}

class Object : public std::enable_shared_from_this<Object>
{
    template<typename T, typename... Args>
    friend std::shared_ptr<T> make_object(Args&&... args);

private:
    Object(Object const &) = delete;
    Object(Object &&) = delete;
    Object & operator = (Object const &) = delete;
    Object & operator = (Object &&) = delete;

    Object(int)
    {
        std::cout << "Created Object" << std::endl;
    }

public:
    virtual ~Object()
    {
        // empty
    }

    void init()
    {
        std::cout << "Initd Object" << std::endl;
    }
};

int main()
{
    auto obj = make_object<Object>(1);
    return 0;
}
