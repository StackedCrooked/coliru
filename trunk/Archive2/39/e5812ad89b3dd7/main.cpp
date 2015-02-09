#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

class Base {
protected:
    string type;
public:
    Base() {
        type = "Base";   
    }

    string getType() {
        return type;   
    }
};

class Derived1: public Base {
    public:
        Derived1() {
            type = "Derived1";
        }
};

void test(list<Base*> list) {
    for (auto item : list) {
        cout << item->getType() << endl;   
    }
}


int main()
{
    list<Base*> base = {new Base(), new Base(), new Base()};
    list<Derived1*> derv1 = {new Derived1(), new Derived1()};
   
   test(base);
   return 0; 
}
