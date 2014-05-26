#include <list>

class Component{};

class Drived :public Component
{
    friend std::list<Component> operator +(const Component &c1,const Component &c2)
    {
        std::list<Component> l;
        l.push_back(c1);
        l.push_back(c2);
        return l;
    }
};

int main()
{
    Drived  a;
    Drived b;
    std::list<Component> l= a+b;
}