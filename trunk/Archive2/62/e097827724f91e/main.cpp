    #include <stdio.h>
    #include <time.h>
    #include <mutex>
    #include <iostream>
    #include <vector>
    
    class Somtn {
      public: 
       static void* operator new (size_t){
         std::cout<< "not in constructor" << std::endl;
         return NULL;
       }
    
    };
    int main(void)
    {
      Somtn* st = new Somtn();

      if(st == NULL){
      std::cout << "its null :o " << std::endl;
      }
    return 0;
    }