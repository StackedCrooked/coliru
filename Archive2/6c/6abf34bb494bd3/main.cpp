#include <boost/any.hpp>
#include <map>
#include <iostream>
#include <string>
#include <memory>

struct Animal {
    std::string type;
};

struct Dog : public Animal {
    constexpr static const char* TYPE = "Dog";
    void bark() const {
        std::cout<<"bow"<<std::endl;
    }
};

struct Cat : public Animal {
    constexpr static const char* TYPE = "Cat";
    void meow() const {
        std::cout<<"meow"<<std::endl;
    }
};

template <typename Animal,typename Message>
std::unique_ptr<Animal> get_extension(Message m) {
    try {
        Animal a( boost::any_cast<Animal>(m[Animal::TYPE]) );
        //for simplicity
        return std::unique_ptr<Animal>(new Animal(a));
    } catch (...) {
        return std::unique_ptr<Animal>();
    }    
}

int main()
{
    std::map<std::string,boost::any> m;
    m[Dog::TYPE] = Dog();
    m[Cat::TYPE] = Cat();
    
    auto dog = get_extension<Dog>(m);
    if (dog)
        dog->bark();
    auto cat = get_extension<Cat>(m);
    if (cat)
        cat->meow();
}
