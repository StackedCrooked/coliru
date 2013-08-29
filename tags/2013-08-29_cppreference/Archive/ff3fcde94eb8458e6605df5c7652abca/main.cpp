#include <string>
#include <iostream>
#include <memory>

using namespace std;

class Entity
{
public:
    Entity()
    {
        cout << "Entity()" << endl;
    }
    virtual ~Entity()
    {
        cout << "~Entity()" << endl;
    }
    virtual string getName()
    {
        return "Entity";
    }
};

class Person : public Entity
{
public:
    Person()
    {
        cout << "Person()" << endl;
    }
    ~Person()
    {
        cout << "~Person()" << endl;
    }
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
    unique_ptr<Entity> p(new Person);
    
    return 0;
}
