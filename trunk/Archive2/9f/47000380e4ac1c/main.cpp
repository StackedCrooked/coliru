#include <memory>
#include <iostream>

class Combatant {
public:
    virtual void doSomething() const { std::cout << "Combatant\n"; }
};

class Warrior : public Combatant {
public:
    virtual void doSomething() const override { std::cout << "Warrior\n"; }
};

class Ranger : public Combatant {
public:
    virtual void doSomething() const override { std::cout << "Ranger\n"; }   
};

int main() {
    int menu;
    std::cin >> menu;
    
    std::shared_ptr<Combatant> c1 (nullptr);
    if (menu == 1)
        c1.reset(new Warrior);
    if (menu == 2)
        c1.reset(new Ranger);
        
    c1->doSomething();
    
    return 0;
}