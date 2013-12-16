#include <stdlib.h>
#include <iostream>

class Base
{

public:
    Base() {}
    virtual void SetUI() { std::cout << __PRETTY_FUNCTION__ << '\n'; }


};

class Derived : public Base
{
public:
    Derived() : Base() {}
    virtual void SetUI(){ std::cout << __PRETTY_FUNCTION__ << '\n'; }

};

class HelperClass
{
private:
    Base * basearray[2];

public:
    HelperClass()
    {
     basearray[0] = new Derived;
     basearray[1] = new Derived;
    }

    Base * getBaseArray(int key)
    {
    return this->basearray[key];
    }
};

int main()
{
  HelperClass hold;
  hold.getBaseArray(0)->SetUI();
  // NOTHING HAPPENS ABOVE, THE CODE DOESN'T EVEN REACH THIS POINT, IT JUST GET'S LOST SOMEWHERE IN     //THE ABOVE STATEMENT.  i KNOW THIS BECAUSE I PUT AN exit(0) inside the function setUI() for both the   //base and derived class and the program doesn't exit.

  return 0;
}
