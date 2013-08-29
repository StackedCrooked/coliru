#include <iostream>

using namespace std;

//define.hpp

class A{
public:

int getA() const;
int getAa() const;

};

ostream& operator<<(ostream& out, const A& obj); // defined outside of the class



//implement.cpp

ostream& operator<<(ostream& out, const A& obj){
    return out << obj.getA() 
                << obj.getAa()
                << endl;
};

int A::getA() const{ return 0; }
int A::getAa() const{ return 0; }

int main(){}
