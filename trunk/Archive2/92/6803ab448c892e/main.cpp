#include <iostream>

struct AI
{
    virtual void think()=0;
        
    struct Fighter;
    
    struct Mage;
};

struct AI::Fighter : public AI
{
    void think()
    {
        std::cout << "Fighter";
    }
};

struct AI::Mage : public AI
{
    void think()
    {
        std::cout << "Mage";
    }
};

int main()
{
    AI * ai = new AI::Fighter;
    ai->think();
}
