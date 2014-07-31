#include <iostream>
struct Foo
{
    Foo(int i){}; 
};
Foo silly_function()
{
    return (1,2,3);
}
/* This, rightfully, fails to compile
Foo not_a_silly_function()
{
    return Foo(1,2,3);
}
*/
int main()
{
   int i= 0;
   while(i++,i<=5)
   {
       std::cout << i << std::endl;
   }
  // this, on the other hand, is just plain silly
   while(i = 0,i++,i<=5)
   {
       std::cout << i << std::endl;
       static int j=0;
       j++;
       if (j>5) break;
   }
   // this is equally stupid, and also does not compile as declarations are not primary expressions
   //while(int i = 0,i++,i<=10)

    
    return 0;
}
