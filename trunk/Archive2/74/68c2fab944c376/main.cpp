#include <iostream>
#include <array>
#include <memory>

class Parent
{
public:
    virtual ~Parent() = default;
    virtual void speak() const
    {
        std::cout << "Parent" << std::endl;
    }
};

class Child : public Parent
{
public:
    void speak() const override
    {
        std::cout << "Child" << std::endl;
    }
};

class GrandChild : public Child
{
public:
    void speak() const final
    {
        std::cout << "GrandChild" << std::endl;
    }
};

class BarrenChild final : public GrandChild
{
public:

    /* This part won't compile
    void speak() const
    {
        std::cout << "BarrenChild" << std::endl;
    }
    */
};

/* This part won't compile
class MiracleChild : public BarrenChild
{
};
*/

int main()
{
    std::array<std::unique_ptr<Parent>, 4> const parents = {std::unique_ptr<Parent>( new Parent() ),
                                                            std::unique_ptr<Parent>( new Child() ),
                                                            std::unique_ptr<Parent>( new GrandChild() ),
                                                            std::unique_ptr<Parent>( new BarrenChild() )};
    
    for(auto const& parent : parents)
    {
        parent->speak();
    }
}
