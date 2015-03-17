#include <iostream>
#include <string>
#include <vector>


int main()
{
    
    system("clear");
    system("pwd");
    system("ls -al");
    
    system ("mkdir ../../m.txt" );
    
    
    for(int i=0; i<5; i++)
    {
        system( "cd .. " );
        system( "pwd" );
    }
    
    
  return 0;
    
}
