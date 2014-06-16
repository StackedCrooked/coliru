#include <iostream>
#include <string>
#include <utility>

class Object
{
public:
    void Test()
    {
        std::cout << "Test" << std::endl;
    }
};

class EmptyObject
{
};

class Base
{
public:
    virtual std::string Foo()
    {
        return "Base";
    }
};

template <typename T>
class Intermediate : public Base
{
    // common operations with m_object

protected: // not private!
    T m_object;
};

template <typename T, typename = bool>
class Derived : public Intermediate<T> {};

template <typename T>
class Derived<T, decltype(std::declval<T>().Test(), void(), true)>
    : public Intermediate<T>
{
public:
    virtual std::string Foo() override
    {
        this->m_object.Test(); // this-> is necessary here!
        return "Derived";
    }
};

int main()
{
    Derived<Object> testObject;
    std::cout << testObject.Foo() << std::endl;

    Derived<EmptyObject> testEmpty;
    std::cout << testEmpty.Foo() << std::endl;
}