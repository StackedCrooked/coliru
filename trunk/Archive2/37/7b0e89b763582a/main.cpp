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
        explicit virus(int strength) : viralCode(strength), generation(1) {};
        virus(const virus& other): viralCode(other.viralCode), generation(other.generation+1) {};
        
        void printData() const {std::cout << "Virus strength: "<<viralCode << ", generation: " << generation << std::endl;};
    private:
        int viralCode;
        int generation;
};

class dummyVirus : public virus
{
    public:
        dummyVirus() = default;
        dummyVirus(int strength): virus(strength) {};
        dummyVirus(const dummyVirus&) = delete; //it can not copy itself;
};

//example to show why explicit is for 1 parameter constructor for virus
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
    
//    virus deadVirus;            //compile error, no viral code
    virus goatVirus{1};
    virus monkeyVirus{3};
    virus humanVirus{monkeyVirus};
    dummyVirus dummy{5};
//    dummyVirus descendant{dummy}; //compile error, dummy virus is not able to copy itself
    
    goatVirus.printData();
    monkeyVirus.printData();
    humanVirus.printData();
    dummy.printData();
    
    
    std::cout << "Explicit examples: " <<std::endl;
    printDummyVirus(dummy);
//    printDummyVirus(6);
    printVirus(goatVirus);
//    printVirus(6);
}
