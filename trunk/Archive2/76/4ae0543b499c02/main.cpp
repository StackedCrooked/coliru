#include <list>

class Component{};

class Drived :public Component
{
    friend std::list<Component> operator +(const Component &c1,const Component &c2)
    {
        return std::list<Component>();
    }
};

int main()
{
    Drived  a;
    Drived b;
    std::list<Component> l= a+b;
}