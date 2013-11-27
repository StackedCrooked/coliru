#include <iostream>
using namespace std;

class Base
{
 public:
    virtual int test(void* arguments[]) 
    {
       cout << "Base function being called. VTable lookup ignored since there is no virtual." << endl;
       cout << *static_cast<string*>(arguments[0]) << endl;
       cout << *static_cast<int*>(arguments[1]) << endl;   
       
       return 0;
    }
};

class Derived : public Base
{
 public:
    virtual int test(void* arguments[]) 
    {
       cout << "Derived functin being called. VTable lookup during runtime. Slight overhead here!" << endl;
       
       cout << *static_cast<string*>(arguments[0]) << endl;
       cout << *static_cast<int*>(arguments[1]) << endl;   
       
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
   
   return 0;
}

// Look at the difference in psuedo-assembly code
// My knowledge in compiler is little, but I can see that
// that there are unncessary cycles being wasted for this part.

// **** With array *****
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
