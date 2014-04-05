#include <iostream>
#include <cstdio>

struct Animal
{
    virtual void yelp() const = 0;
};

struct Dog : public Animal
{
    void yelp() const { printf("Bark!\n"); }
};

struct Person 
{ 
    virtual ~Person() { }
    virtual void poke(const Animal& a) = 0; 
};

struct Retard : public Person
{ 
    void poke(const Animal& a) 
    { 
        a.yelp();
    }
};
    
int main()
{
    Dog dog;
    Person* b_instance = new Retard;
    
    b_instance->poke(dog);
    
    delete b_instance;
    return 0;
}
