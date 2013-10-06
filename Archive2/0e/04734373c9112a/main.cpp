#include <iostream>

template<class T>
class Variable {
protected:
    T value;
    std::string name;   
public:
    Variable(std::string n, T v) {
        name = n;
        value = v;
    }
    Variable (const Variable& other) {
        value = other.value;
        name = other.name;
    }
    virtual ~Variable(){};
    T getVal() { return value; }
};

int main(int, char*[]) {
    Variable<bool> condition("Name", true);
    Variable<char> character("Name2", 'T');
    Variable<unsigned> integer("Name3", 123);
    std::cout << condition.getVal() << '\n';
    std::cout << character.getVal() << '\n';
    std::cout << integer.getVal() << '\n';
}