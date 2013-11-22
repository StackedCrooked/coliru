#include <boost/any.hpp>
#include <map>
#include <iostream>
#include <string>
#include <memory>
#include <functional>

struct Message {
    std::string animal_type;
};

struct Animal {
    virtual void speak() const = 0;
    virtual ~Animal(){}
};

struct Dog : public Animal {
    constexpr static const char* TYPE = "Dog";
    virtual void speak() const {
        std::cout<<"bow"<<std::endl;
    }
};

struct Cat : public Animal {
    constexpr static const char* TYPE = "Cat";
    virtual void speak() const {
        std::cout<<"meow"<<std::endl;
    }
};

struct AnimalRegistry {
    std::map<std::string , std::function<std::unique_ptr<Animal>()>> creators;
    
    template<typename A>
    void register_creator() {
        creators[A::TYPE] = []() { return std::unique_ptr<Animal>(new A); };
    }
    
    template<typename Message>
    std::unique_ptr<Animal> create(Message m) {
        return creators[m.animal_type]();
    }
};

int main()
{
    AnimalRegistry registry;
    registry.register_creator<Dog>();
    registry.register_creator<Cat>();
    
    Message received_message { "Dog" /*this is a part of your protobuf*/ };
    
    auto dog = registry.create(received_message);
    if (dog)
        dog->speak();
        
    Message another_message { "Cat" };
    auto cat = registry.create(another_message);
    if (cat)
        cat->speak();
}
