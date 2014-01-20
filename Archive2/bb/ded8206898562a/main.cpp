#include <iostream>
 
int main()
{
    // simple if-statement with an else clause
    int i = 2;
    if (i > 2) {
        std::cout << i << " is greater than 2\n";
    } else {
        std::cout << i << " is not greater than 2\n";
    }
 
    // nested if-statement
    int j = 1;
    if (i > 1)
        if(j > 2)
            std::cout << i << " > 1 and " << j << " > 2\n";
        else // this else is part of if(j>2), not part of if(i>1) 
            std::cout << i << " > 1 and " << j << " <= 2\n";
 
   // declarations can be used as conditions with dynamic_cast
   struct Base {
        virtual ~Base() {}
   };
   struct Derived : Base {
       void df() { std::cout << "df()\n"; }
   };
   Base* bp1 = new Base;
   Base* bp2 = new Derived;
 
   if(Derived* p = dynamic_cast<Derived*>(bp1)) // cast fails, returns NULL
       p->df();  // not executed
 
   if(auto p = dynamic_cast<Derived*>(bp2)) // cast succeeds
       p->df();  // executed
}