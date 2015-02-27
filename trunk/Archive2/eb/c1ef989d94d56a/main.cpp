#include <iostream>
#include <memory>
#include <string>
#include <type_traits>

template<typename T>
void ping(T * thing)
{
    if(typeid(typename T::base_type) != typeid(T)) {
        ping<typename T::base_type>(thing);
    }
    thing->T::Ping();
}

class Base
{
public:
    Base()
    { }

    virtual void Ping() { std::cout << "Ping base!" << std::endl; }

    typedef Base base_type;
};

class Derived : public Base
{
public:
    Derived() :
        Base()
    { }

    void Ping() { std::cout << "Ping derived!" << std::endl; }

    typedef Base base_type;
};

class Derivederer : public Derived
{
public:
    Derivederer() :
        Derived()
    { }

    void Ping() { std::cout << "Ping derivederer!" << std::endl; }

    typedef Derived base_type;
};


int main()
{
    Derivederer d;
    ping(&d);
    return 0;
}
