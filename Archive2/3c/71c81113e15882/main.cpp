#include <iostream>
using namespace std;
 
class Time
{
   private:
      int hours;             // 0 to 23
      int minutes;           // 0 to 59
   public:
      // required constructors
      Time(){
         hours = 0;
         minutes = 0;
      }
      Time(int h, int m){
         hours = h;
         minutes = m;
      }
      // method to display time
      void displayTime()
      {
         
      }
      // overloaded prefix ++ operator
      Time operator-- ()  
      {
                  
         if(minutes == 00)  
         {
            --hours;
            minutes=59;
         }else{
         --minutes; }
         return Time(hours, minutes);
      }
      // overloaded postfix ++ operator
      Time operator++( int )         
      {
         // save the orignal value
         Time T(hours, minutes);
         // increment this object
         ++minutes;                    
         if(minutes >= 60)
         {
            ++hours;
            minutes -= 60;
         }
         // return old original value
         return T; 
      }
};
int main()
{
    printf("%05d",23);
   unsigned int minutes = (int) (1 / 60) % 60;
    unsigned int seconds = (int)  2  % 60;
  
   cout<<endl;
cout<<seconds;
   return 0;
}