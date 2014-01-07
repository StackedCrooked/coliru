#include <cstdlib>
#include <iostream>

char *a = NULL;
bool allmem(int n);
bool freemem();

int main()
{
   bool t = allmem(9);
   if(t)
    printf("true");
   else
    printf("false");
   bool x = freemem();
   if(x)
    printf("true");
   else
    printf("false");
}

bool allmem(int n)
{
 a = static_cast<char *>(std::malloc(n *1024*1024*1024* sizeof(char) ));
 printf("%lu",sizeof(a));
    if (a != nullptr) 
    {
     //free(a);
     return true;
    }
    else
     return false;
}

bool freemem()
{
  
  std::free(a);
  a=NULL;
  if(a != NULL)
   return false;
  else
   return true;
}