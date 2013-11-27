#include <iostream>
using namespace std;

class SampleClass
{
 public:
    int test(void* arguments[]) {
       cout << *static_cast<string*>(arguments[0]) << endl;
       cout << *static_cast<int*>(arguments[1]) << endl;
       
       return 0;
    }
};

int main()
{   
   SampleClass lol;
   string * str = new string("sunny");
   int * vale = new int(20);
   
   void * arguments [] = { str, vale };
   lol.test(arguments);
   
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
