#include <iostream>

namespace France
{
    class Person
    {
    };
    
    void speak(const Person &)
    {
        std::cout << "Bonjour!" << std::endl;
    }
}

namespace England
{
    class Person
    {
    };
    
    void speak(const Person &)
    {
        std::cout << "Hello!" << std::endl;
    }
}

int main()
{
    France::Person claude;
    speak(claude);
    
    England::Person harry;
    speak(harry);    
}
