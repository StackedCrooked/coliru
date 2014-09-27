#include <string>
#include <iostream>
using std::string;

class Person
{
public:
    Person(string s = "", int age = 0) :Name(s), Age(age) {}
    operator string() const { return Name; }
    explicit operator int() const{ return 10; }  // ! Explicit
    explicit operator double()const { return 20; } //! Explicit
    operator bool()const { std::cout<<"op(bool)\n"; if (Name != "") return true; return false; }
    string Name;
    int Age;
};

int main(){

    Person a;
    int z = a;
    std::cout << z << std::endl;   // Why print "1"?
}