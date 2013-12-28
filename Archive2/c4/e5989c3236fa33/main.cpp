#include <iostream>
#include <memory>
 

class myClass
{
    public:
    myClass (int i) { std::cout << i << "\n"; }
    ~myClass()      { std::cout << "I Rule Da Universe ! ! !\n"; }
};

class myOtherClass
{
    public:
    myOtherClass (int i) { std::cout << i << "\n"; }
    ~myOtherClass()      { std::cout << "I REALLY DO ! ! !\n"; }
};

void myFunc ()
{
    std::unique_ptr<myClass> mine (new myClass(99));
    auto *myNew = new myOtherClass(11);
    delete myNew;
}

int main()
{
    std::cout << "Before The class. \n";
    myFunc();
    std::cout << "After the class.  \n";

}