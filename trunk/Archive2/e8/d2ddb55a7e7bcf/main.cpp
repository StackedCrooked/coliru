#include <iostream>

template<typename T>
class Parent
{
    protected:
        virtual int Show()
        {
            std::cout<<"Parent::Show Called\n";
            return 0;
        }
};

class Child : Parent<Child>
{
    protected:
        virtual int Show() final override
        {
            std::cout<<"Child::Show Called\n";

            //supposed to be in a thread in my original code.
            auto call_parent = [&] {
                //Parent<Child>::Create(); //call other parent functions..
                return Parent<Child>::Show();
            };

            return call_parent();
        }
};

int main() {}