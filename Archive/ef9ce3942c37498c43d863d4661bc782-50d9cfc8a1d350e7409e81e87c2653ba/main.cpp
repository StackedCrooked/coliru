#include <iostream>
#include <string>


struct Person
{
    explicit Person(const std::string & name) : name(name) {}
    
    explicit operator const std::string &() const
    {
        return name;
    }
    
    std::string name;
};


int main()
{
    Person p("John");
    std::cout << std::string(p) << std::endl; // conversion constructor is copy?
}
