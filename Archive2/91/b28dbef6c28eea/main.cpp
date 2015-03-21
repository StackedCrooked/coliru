#include <string>
#include <iostream>
#include <list>
#include <vector>

class Base{
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
