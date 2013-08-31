#include <iostream>
#include <string>
#include <list>

using namespace std;

class Component {
public:

    Component() {};

    ~Component() {};
    
    virtual std::string ToString() const {
        return "OOPS! Default `ToString` called";
    }
};

class CComputer {
public:
    // constructor    
    CComputer(string name) {
        this->name = name;
    };
    // overloaded operator << for printing
    friend ostream& operator<<(ostream& os, const CComputer& c);

    // adds some component for this computer
    CComputer & AddComponent(Component const & component) {
        this->listOfComponents.push_back(component);
        return *this;
    };

    // sets address for this computer
    CComputer & AddAddress(const string & address) {
        this->address = address;
        return *this;
    };
    
    void PrintAll() {
        for (auto&& component : listOfComponents)
            std::cout << component.ToString() << '\n';
    }

    string name;
    string address;
    list<Component> listOfComponents;
};

class CCPU : public Component {
public:

    CCPU(int cores, int freq) {
        this->cores = cores;
        this->freq = freq;
    };
    
    std::string ToString() const {
        return "CCPU::ToString()";
    }

    int cores;
    int freq;
};

class CMemory : public Component {
public:

    CMemory(int mem) {
        this->mem = mem;
    };
    
    std::string ToString() const {
        return "CMemory::ToString()";
    }

    int mem;
};

int main() {
    CComputer c("test.com");
    c.AddAddress("123.45.678.910") .
        AddComponent(CCPU(8, 2400)) .
        AddComponent(CCPU(8, 1200)).
        AddComponent(CMemory(2000)).
        AddComponent(CMemory(2000));
        
    c.PrintAll();
}