#include <iostream>
using namespace std;

class Animal
{
public:
//void eat() { std::cout << "I'm eating generic food." << endl; }
virtual void eat() { std::cout << "I'm eating generic food." << endl; }
};

class Cat : public Animal
{
public:
void eat() { std::cout << "I'm eating a rat." << endl; }
};

void func(Animal *xyz) { xyz->eat(); }

int main (){
    Animal *animal = new Animal;
    Cat *cat = new Cat;
    
    animal->eat(); // outputs: "I'm eating generic food."
    cat->eat();    // outputs: "I'm eating a rat."
    
    cout << endl;
    
    func(animal); // outputs: "I'm eating generic food."
    func(cat);    // outputs: 
    
}