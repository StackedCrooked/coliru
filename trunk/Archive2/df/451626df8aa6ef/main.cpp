#include <string>

using namespace std;
class Animal
{
protected:
    string animalName, sounds, colors, wayOfDrinking, wayOfEating;
    int numberOfLegs;
    bool hasTail;

public:
    Animal() {} //default constructor
    ~Animal() {} //destructor

    void SetAnimal(string, string, string, string, string, int, bool) { }
    Animal GetAnimal(void);
};

class WildAnimal : public Animal
{
    string animalPrey, attackStyle;

public:
    void SetAnimal(string, string) { }
    using Animal::SetAnimal;
};

class TameAnimal : public Animal
{
    string predator, hidingStyle;
};

int main() {
    WildAnimal lion;
    lion.SetAnimal("Lion", "Roar!", "Gold", "Stick the tongue out", "Tear the flesh", 4, true);
    lion.SetAnimal("Stag", "Pounce");
}
