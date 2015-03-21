#include <string>
#include <iostream>
#include <list>
#include <vector>

class Base{
    Base(const Base&) =default;
};

class Son;
class Daughter: public Base{
public:
    Daughter(Son* s) : Base(*s){};
};

class Son: public Base{
public:
    Son(Daughter* d) : Base(*d){};
};

int main(){
}
