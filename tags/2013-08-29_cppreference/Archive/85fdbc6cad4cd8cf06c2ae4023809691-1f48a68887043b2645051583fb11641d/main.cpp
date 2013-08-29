#include <iostream>

class Human {
public:
    size_t age;
    Human(): age(0) {
        std::cout << "Human born\n";
    }
    void birthday() {
        ++age;
    }
    ~Human() {
        std::cout << "Human died at " << age << " years old\n";
    }
};

int main() {
    Human* person = new Human;
    person->age = 58;
    person->birthday();
    delete person;
    std::cout << "Hah!";
}