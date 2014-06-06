#include <iostream>
union bob
{
    
  bob(int) : i{3}{};
  bob(long) : j{4}{};
  bob(char) : c{'e'}{};
  
  int i;
  long j;
  char c;
   
};
int main()
{
    bob a{3};
    bob b{(long)3};
    bob c{'c'};
    
    
}