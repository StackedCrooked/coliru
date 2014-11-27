#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <functional>
#include <exception>

template <typename T>
class Container {
    const T t;

    public:

    Container(const T& _t): t(_t) { }    

    const T& get() {
        return t;
    }
};

struct Person {
    int age;
    Person(int _age): age(_age) {}; 
};


class PersonContainer {
    const Person& p;

    public:

    PersonContainer(const Person& _p): p(_p) { }    

    const Person& get() {
        return p;
    }
};

int main() {    
    PersonContainer personContainer(Person(50));
    Container<Person> container(Person(50));
    std::cout << personContainer.get().age;
    std::cout << container.get().age;
    return 0;
}