#include <iostream> 
using namespace std; 

/*
    Example of how to constructors when statically initializing a
    class array.
*/

class MyClass {
public:
    const char *name;
    int num;

    MyClass(const char *s, int i) : name(s), num(i) {} 
};

MyClass classArray[] = { 
    MyClass("First",  1), 
    MyClass("Second", 2),
    MyClass("Thrid",  3),
    MyClass("Fourth", 4) 
};
 
int main() 
{ 
    for(int i=0; i < 4; i++) {
        auto c = &classArray[i];
        cout << "MyClass '" << c->name << "' has value '" << c->num << "'\n";
    }
 
    return 0; 
}