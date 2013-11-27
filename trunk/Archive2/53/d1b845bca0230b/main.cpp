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
   
   void * arguments [] = { static_cast<void*>(str), static_cast<void*>(vale) };
   lol.test(arguments);
   
   return 0;
}
