#include <iostream>
#include <string>
#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

//Constructor attributes(?)
//no need to hide constructors under private: any more
class virus
{
    public:
        virus() = delete;  //a virus must have a viral code, so I deleted the default constructor;
        explicit virus(int strength) 
            : viralCode(strength)
            , generation(1) 
        {};
        
        virus(const virus& other)
            : viralCode(other.viralCode)
            , generation(other.generation+1) 
        {};

    public:    
        void printData() const 
        {
            std::cout << "Virus strength: "<< viralCode << ", generation: " << generation << std::endl;
        };

    private:
        int viralCode;
        int generation;
};

//dummy virus is so dummy that it can not copy itself;
class dummyVirus : public virus
{
    public:
        dummyVirus() = default;         //default contructor would call the default constructor of the base. Which is deleted.
        //dummyVirus() {};              //it does not work, even if we create the contructor like this
        dummyVirus(int strength)
            : virus(strength) 
        {};
        dummyVirus(const dummyVirus&) = delete; //prevent copy
};

//for showing what explicit keyword does
void printVirus(const virus& virus)
{
    virus.printData();
}

void printDummyVirus(const dummyVirus& virus)
{
    virus.printData();
}

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
    
//    virus deadVirus;            //compile error, no default constructor
    virus goatVirus{1};
    virus monkeyVirus{3};
    virus humanVirus{monkeyVirus};  //copy itself, incrementing generation
    
//    dummyVirus dummyDefault;        //compile error, defaulted constructor which would call deleted base constructor
    dummyVirus dummy{5};
//    dummyVirus descendant{dummy}; //compile error, deleted copy constructor
    
    goatVirus.printData();
    monkeyVirus.printData();
    humanVirus.printData();
    dummy.printData();
    std::cout << std::endl;
    
    std::cout << "Explicit examples: " << std::endl;
    printDummyVirus(dummy);
    printVirus(goatVirus);
    
    std::cout << "Implicit conversion examples: " <<std::endl;
    printDummyVirus(6);       //works, implicit conversion from int to DummyVirus(int) - compiler can do this with 1 parameter constructors.
//    printVirus(6);          //does not work, 1 parameter constructor set to be explicit.
    printVirus(virus(6));     //works, we created a virus object.
}
