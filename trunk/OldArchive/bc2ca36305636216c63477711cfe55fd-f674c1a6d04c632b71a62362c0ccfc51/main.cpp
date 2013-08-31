#include <iostream>
int  main()
{
   for(const auto & el : { "Hello", "from", "GCC", __VERSION__, "!" } )
     std::cout << el << ' ' ;
     
   std::cout << std::endl;
   
}
