    #include <stdio.h>
    #include <time.h>
    #include <mutex>
    #include <iostream>
    #include <vector>
#include <bitset>

const int numberOfRatingInfo = 3;
class CdrRatingInfoSomething {
  
  const int premiumBit = 0;
  
  std::bitset<numberOfRatingInfo> ratingInfo;
  public:
  CdrRatingInfoSomething(int ratingMask){
   this->ratingInfo = ratingMask;   
  }
  bool isPremium(){
   return   ratingInfo[premiumBit];
  }
  
  
  
};


int main(){
     
     CdrRatingInfoSomething cdrRatingInfo(1);
     std::cout << cdrRatingInfo.isPremium() << std::endl;
 
 
}