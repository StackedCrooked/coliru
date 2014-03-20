#include <iostream>



/**
 * This is my latest silly invention :)
 * 
 * It takes the method-chain-configuration mechanism a step further by
 * enforcing a certain order of initializiation.
 * 
 */


struct Person
{
    struct Children
    {
        Person children(int n)
        {
            person_->children_ = n;
            return *person_;
        }

        Person* person_;
    };

    struct Married
    {
        Children married(bool y)
        {
            person_->married_ = y;
            return { person_ };
        }

        Person* person_;
    };

    struct Age
    {
        Married age(int age)
        {
            person_->age_ = age;
            return { person_ };
        }

        Person* person_;
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
    john.name("john").age(55).married(false).children(23);
    
    std::cout << john.name_ << " is " << john.age_ <<  " years old. He is" << (john.married_ ? " " : " not ") << "married and has " << john.children_ << " children." << std::endl;
    
}
