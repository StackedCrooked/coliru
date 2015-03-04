#include <iostream>
#include <array>
#include <memory>

class Parent
{
public:
    virtual ~Parent() = default;
    virtual void speak() const
    {
        std::cout << typeid(*this).name() << std::endl;
    }
};

class Child : public Parent
{
public:
    void speak() const override
    {
        std::cout << typeid(*this).name() << std::endl;
    }
};

class GrandChild : public Child
{
public:
    void speak() const final
    {
        std::cout << typeid(*this).name() << std::endl;
    }
};

int main()
{
    std::array<std::unique_ptr<Parent>, 3> const parents = {std::unique_ptr<Parent>(new Parent()),
                                                            std::unique_ptr<Parent>(new Child()),
                                                            std::unique_ptr<Parent>(new GrandChild())};
    
    for(auto const& parent : parents)
    {
        parent->speak();
    }
}
