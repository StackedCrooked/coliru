#include <vector>                                              
#include <iostream>                                            
                                                               
int main()                                                     
{                                                              
  std::vector<bool> doors(100, false);                         
                                                               
  for (int wife = 1; wife <= 100; ++wife)                      
  {                                                            
    for (int door = 1; door <= 100; ++door)                    
    {                                                          
      if (door % wife == 0)                                    
      {                                                        
        for (int turn = 0; turn < wife; ++turn)                
        {                                                      
          if (doors[door-1] == true) { doors[door-1] = false; }
          else { doors[door-1] = true; }                       
        }                                                      
      }                                                        
    }                                                          
  }                                                            
                                                               
  for (int door = 1; door <= 100; ++door)                      
  {                                                            
    if (doors[door-1] == true)                                 
    {                                                          
      std::cout << door << " ";                             
    }                                                          
  }                                                            
                                                               
  return 0;                                     
}                                                              
