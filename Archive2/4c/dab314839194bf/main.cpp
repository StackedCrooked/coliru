#include <iostream>
#include <stdarg.h>
#include <string>
 
void print(int var1, ...)
{
  va_list LIST;
  va_start(LIST, var1);
  
  std::cout<<var1<<'\n';
  
  char var2 = (char)va_arg(LIST, int);
  std::cout<<var2<<'\n';
  
  const char* var3=va_arg(LIST, char*);
  std::cout<<var3<<'\n';
  
  va_end(LIST); 
}
int main()
{
    print(1,'a',"qwe");
}