class Animal
{
public:
    virtual void walk() const = 0;
};

class Dog : public Animal
{
public:
    virtual void walk() override;
};

void Dog::walk() {}
