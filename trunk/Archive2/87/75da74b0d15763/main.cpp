    #include <stdio.h>
    #include <time.h>
    #include <mutex>
    #include <iostream>
    #include <vector>
    #include <bitset>


class CdrRatingInfoSomething {
  static const int numberOfRatingInfo = 3;
  
  static const int premiumBit = 0;
  static const int isOfflineBit = 1;
  
  std::bitset<numberOfRatingInfo> ratingInfo;
  
  public:
      CdrRatingInfoSomething(int ratingMask){
        this->ratingInfo = ratingMask;   
      }
      bool isPremium()
      {
       return   ratingInfo[premiumBit];
      }
      void setPremium()
      {
          ratingInfo[premiumBit] = 1;
      }
    bool isOffline()
      {
       return   ratingInfo[isOfflineBit];
      }
      void setOfflineBit()
      {
          ratingInfo[isOfflineBit] = 1;
      }
  
};


int main(){
     
     CdrRatingInfoSomething cdrRatingInfo(1);
     std::cout << cdrRatingInfo.isPremium() << std::endl;
   std::cout << cdrRatingInfo.isOffline() << std::endl;
 
}