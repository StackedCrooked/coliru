#include <unistd.h>
#include <stdlib.h>
#include <iostream>

void function(int i)
{
   if (i >= 10)
      return;

   auto f = [&](void)
   {
      std::cerr << "Call " << i << std::endl;
      function(i+1);
   };
   
   f();
}

int main(int argc, char **argv) 
{
   function(0);
   return 0;
}
