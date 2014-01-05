#include <iostream>                                                                       
                                                                                          
template<typename T, int MeaningOfLife>                                                   
struct Fun                                                                                
{                                                                                         
   Fun()                                                                                  
   {                                                                                      
      std::move(*this).how(MeaningOfLife);                                                
   }                                                                                      
                                                                                          
   T how(int i)&&                                                                         
   {                                                                                      
      using namespace std;                                                                
      cout << "how ";                                                                     
      return std::move(*this).areyou(i);                                                  
   }                                                                                      
                                                                                          
   T areyou(int i)&&                                                                      
   {                                                                                      
      using namespace std;                                                                
      cout << "are you?" << endl;                                                         
      return std::move(*this).how(i);                                                     
   }                                                                                      
};                                                                                        
                                                                                          
                                                                                          
int main()                                                                                
{                                                                                         
   Fun<void, 42>();                                                                       
} 