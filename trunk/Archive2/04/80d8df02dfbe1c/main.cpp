#include <iostream>
#include <string>
#include <vector>
#include <ostream>


class Person
{
    public:
        Person() : d_age(0), d_name(""){}
        Person(int age, std::string name) : d_age(age), d_name(name){}
        
        inline int age() const { return d_age; }
        inline std::string name() const { return d_name; }
        
        friend bool operator==(const Person &lhs, const Person &rhs)
        {
            return  lhs.age() == rhs.age();    
        }
        
        
    private:
    
        friend std::ostream& operator<<(std::ostream &stream, const Person &person)
        {
            stream << "name: " << person.d_name << " age: " << person.d_age;            
            return stream;
        }
        
        
        int d_age;
        std::string d_name;
};

int main()
{
    std::vector<Person> people;
    
    people.push_back(Person(31, "alter"));
    people.push_back(Person(31, "Prashastha"));
    
    for (unsigned int i = 0; i < people.size(); i ++)
    {
        std::cout << people[i] << std::endl;   
    }    
    
    bool sameage = people[0] == people[1];
    
    std::cout << "same age " << sameage << std::endl;
}
