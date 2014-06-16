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
class Intermediate1 : public Base
{
    // common operations with m_object

protected: // not private!
    T m_object;
};

template <typename T, typename = bool>
class Intermediate2 : public Intermediate1<T> {};

template <typename T>
class Intermediate2<T, decltype(std::declval<T>().Test(), void(), true)>
    : public Intermediate1<T>
{
public:
    virtual std::string Foo() override
    {
        this->m_object.Test(); // this-> is necessary here!
        return "Derived";
    }
};

template <typename T>
class Derived : public Intermediate2<T> { /* ... */ };

int main()
{
    Derived<Object> testObject;
    std::cout << testObject.Foo() << std::endl;

    Derived<EmptyObject> testEmpty;
    std::cout << testEmpty.Foo() << std::endl;
}