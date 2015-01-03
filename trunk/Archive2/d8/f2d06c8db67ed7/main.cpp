#include <functional>
#include <iostream>
#include <string>
#include <map>

class api {
    // maps containing the different function pointers
    typedef void(*voidfuncptr)();
    typedef int(*stringcrintptr)(std::string, const int&);

    std::map<std::string, voidfuncptr> voida;
    std::map<std::string, stringcrintptr> stringcrint;
public:
    // api temp class
    // given an api and a name, it converts to a function pointer
    // depending on parameters used
    class apitemp {
        const std::string n;
        const api* p;
    public:
        apitemp(const std::string& name, const api* parent)
            : n(name), p(parent) {}
        operator voidfuncptr()
        { return p->voida.find(n)->second; }
        operator stringcrintptr()
        { return p->stringcrint.find(n)->second; }
    };

    // insertion of new functions into appropriate maps
    void insert(const std::string& name, voidfuncptr ptr)
    { voida[name]=ptr; }
    void insert(const std::string& name, stringcrintptr ptr)
    { stringcrint[name]=ptr; }
    // operator[] for the name gets halfway to the right function
    apitemp operator[](std::string n) const
    { return apitemp(n, this); }
};

api myMap; 

void bla() {
    std::cout << "Hello World!" << std::endl;
}

int hello_world(std::string name, const int & number )
{
    name += "!";
    std::cout << "Hello, " << name << std::endl;
    return number;
}

int main()
{
    myMap.insert("my_method_hello", &hello_world );
    myMap.insert("my_bla", &bla );
    
    int a = myMap["my_method_hello"]("Tim", 25);
    myMap["my_bla"]();
}