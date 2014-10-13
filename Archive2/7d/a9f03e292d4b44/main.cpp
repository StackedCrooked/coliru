// to create a class Person and specialize the hash function 

#include <string>
#include <iostream>

class Person {
    friend bool operator==(const Person&, const Person&);
    public:
        friend struct std::hash<Person>;
        Person(std::string name, int age) : name(name), age(age) {}
        ~Person() = default;
    private:
        std::string name;
        int age;
};

namespace std{
 
 template<>
 struct hash<Person> {
   using argument_type = Person;
   using result_type = size_t;
   
   size_t operator()(const Person &person) const {
        return hash<std::string>()(person.name) ^ hash<int>()(person.age);   
   }
 };
    
}

bool operator==(const Person &lhs, const Person &rhs) {
    return lhs.name == rhs.name && lhs.age == rhs.age;
}

int main()  {
    Person ufuoma("Ufuoma", 27);
    std::cout << std::hash<Person>()(ufuoma) << std::endl;
}