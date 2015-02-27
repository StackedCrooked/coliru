#include <iostream>
#include <string>
#include <vector>

class Entity;

class SubEntity
{
public:
    SubEntity()
    {
        m_entity.coucou();
    }

private:
    Entity m_entity;
};

class Entity
{
public:
    void coucou()
    {
        std::cout << "Coucou" << std::endl;
    }
    
private:
    SubEntity m_subEntity;
};

int main()
{
    return (0);
}
