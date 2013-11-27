#include <iostream>
using namespace std;

// Look at the difference in psuedo-assembly code
// My knowledge in compiler is little, but I can see that
// that there are unncessary cycles being wasted for this part.

// **** With array (this example) *****
// LOAD         Reg, memAddressOfArray
// WRITETOMEM   Reg, ptrToVar1
// INCREMENT    sp
// WRITETOMEM   Reg, ptrToVar2
// DECREMENT    sp
// PUSH         ptrToArray
// JUMP         test

//  ***** IDEALLY SUPPOSED TO LIKE THIS *****
// PUSH        ptrToVar2
// PUSH        ptrToVar1
// JUMP        test

class Base
{
 public:
    virtual int test(void* arguments[]) 
    {
       cout << "Base function being called. VTable lookup ignored since there is no virtual." << endl;
       cout << *static_cast<int*>(arguments[0]) << endl;   // Parameter 1 (Thinks there is only 1 parameter!)
       
       return 0;
    }
};

class Derived : public Base
{
 public:
    virtual int test(void* arguments[]) 
    {
       cout << "Derived function being called. VTable lookup during runtime. Slight overhead here!" << endl;
       
       cout << *static_cast<string*>(arguments[0]) << endl; // Parameter 1
       cout << *static_cast<int*>(arguments[1]) << endl;   // Parameter 2
       
       return 0;
    }
};

int main()
{   
   Base * base = new Derived;
   
   string * str = new string("sunny");
   int * vale = new int(20);
   
   void * arguments [] = { str, vale };
   
   base->test(arguments);
   
   cout << "NOTE: Derived class has no extra methods although the parameter counts are different.\n      Parent class doesn't even realize parameter 1 exists!" << endl;
   
   return 0;
}
