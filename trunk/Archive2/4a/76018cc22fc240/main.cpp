#include <iostream>

using namespace std;

struct Animal {
    virtual ~Animal() = default;
    virtual Animal& operator=(const Animal& a) = 0;
    virtual string name() const = 0;
    virtual string speak() const = 0;
};

class Sheep : public Animal {
public:
    Sheep() : sound("baaah~") {}
    Animal& operator=(const Animal& a) {
        sound = a.speak();
        return *this;
    }
    string name() const { return string("sheep"); }
    string speak() const { return sound; }
private:
    string sound;
};

class Cow : public Animal {
public:
    Cow() : sound("mooo~") {}
    Animal& operator=(const Animal& a) {
        sound = a.speak();
        return *this;
    }
    string name() const { return string("cow"); }
    string speak() const { return sound; }
private:
    string sound;
};

int main()
{
    Animal* sheep = new Sheep;
    Animal* cow = new Cow;
    cout << "The " << sheep->name() << " says: " << sheep->speak() << endl;
    cout << "The " << cow->name()   << " says: " << cow->speak()   << endl;
    *sheep = *cow;  // slicing!
    cout << "The " << sheep->name() << " says: " << sheep->speak() << endl;
    cout << "The " << cow->name()   << " says: " << cow->speak()   << endl;
    cout << "You can make the sheep speak like a cow, but it will always be a sheep at heart." << endl;
    cout << "In other words: you can copy/move base class values without \"slicing\" derived data," << endl;
    cout << "but you cannot avoid slicing the vtable." << endl;
    delete sheep;
    delete cow;
    return 0;
}
