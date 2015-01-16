#include <iostream>
#include <cmath>
#include <thread>
#include <future>
#include <functional>
#include <vector>
#include <stdint.h>
#include <iostream>
#include <sstream>
#include "boost/format.hpp"

class foo{
    
    int var;
    
    public:
        foo(){
        var = 5;
    };
    
    int testf(){
        if(this == nullptr){
            return 0;
        }else{
            return var;
        }
    }
};

int main()
{
   std::shared_ptr<foo> fooPtr;
   
   std::cout << fooPtr->testf();
   
   fooPtr.reset(new foo());
   
      std::cout << fooPtr->testf();
   
 }