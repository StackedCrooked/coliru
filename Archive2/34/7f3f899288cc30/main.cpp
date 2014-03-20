#include <utility>


/**
 * This is my latest silly invention :)
 */


struct Person
{
    struct Children
    {
        Person children(int n)
        {
            _person->children_ = n;
            return *_person;
        }

        Person* _person;
    };

    struct Married
    {
        Children married(bool y)
        {
            _person->married_ = y;
            return { _person };
        }

        Person* _person;
    };

    struct Age
    {
        Married age(int age)
        {
            _person->age_ = age;
            return { _person };
        }

        Person* _person;
    };

    Age name(const char* name)
    {
        name_ = name;
        return { this };
    }

    const char* name_;
    int age_;
    bool married_;
    int children_;
};


int main()
{
    Person john;
    
    // intellisense guides you through the setters
    // it does not allow you to switch the order
    john.name("john").age(55).married(true).children(10);
    
}


