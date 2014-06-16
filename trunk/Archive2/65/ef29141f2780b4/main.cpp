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

template <typename T, typename = bool>
class Intermediate : public Base
{
};

template <typename T>
class Intermediate<T, decltype(std::declval<T>().Test(), void(), true)>
    : public Base
{
public:
    virtual std::string Foo() override
    {
        this->m_object.Test();
        return "Derived";
    }

protected:
    T m_object;
};

template <typename T>
class Derived : public Intermediate<T>
{
};

int main()
{
    Derived<Object> testObject;
    std::cout << testObject.Foo() << std::endl;

    Derived<EmptyObject> testEmpty;
    std::cout << testEmpty.Foo() << std::endl;
}