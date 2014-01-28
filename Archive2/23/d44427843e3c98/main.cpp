#include <iostream>

class foo
{
public:
    int data;
};

class bar
{
public:
    void function(foo *ptr); //error points to this line
};

void bar::function(foo *ptr)
{
ptr->data = 1; //do something with data inside foo class.
}



int main()
{

foo foo1; //init foo as foo1.

foo *ptr_foo; //pointer of type foo called ptr_foo

ptr_foo = &foo1; //point ptr_foo to the address of foo1

bar bar1; //init bar as bar1

bar1.function(ptr_foo); //call function1 and pass the address of our instance of foo to it.

}