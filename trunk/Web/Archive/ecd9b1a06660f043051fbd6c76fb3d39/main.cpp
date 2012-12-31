#include <string>
#include <iostream>

using namespace std;

class Entity
{
public:
    Entity() {}
    ~Entity() {}
    virtual string getName()
    {
        return "Entity";
    }
};

class Person : public Entity
{
public:
    Person() {}
    ~Person() {}
    string getName()
    {
        return "Person";
    }
    int getAge()
    {
        return 60;
    }

};

int main()
{
    Entity* e = new Entity();

    cout << dynamic_cast<Person*>(e)->getAge();

    delete e;

    return 0;
}
