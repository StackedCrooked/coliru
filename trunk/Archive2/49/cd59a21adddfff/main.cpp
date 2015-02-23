#include <cstdarg>
#include <iostream>
    
struct Foo
{
    void bar(...)
    {  
        std::va_list args; 
	    va_start(args, this);
	  auto n = va_arg(args, int);
	  std::cout << n << "\n";
      	
    	  va_end(args);
    }
    
};
    
int main()
{
    Foo f;
    f.bar(5);    
}