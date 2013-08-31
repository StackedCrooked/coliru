#include <iostream>
#include <iterator>
#include <sstream>

int strtoint(std::string& c)
{
    std::stringstream ss;
    ss << c;
    
    int x = 0;
    ss >> x;
    return x;
}


int main() {
  int date = 130115; // YY MM DD
  
  std::stringstream ss;
  ss << date;
  
  std::string str(ss.str());
  
  int count = 0;
  int div = 0;
  int year = 0;
  int month = 0;
  int day = 0;
  
  std::string syear;
  std::string smonth;
  std::string sday;
  
  for (auto s : str)
  {
      if (count <= 1)
        div = 0;
      else if (count >= 1 && count <= 3)
        div = 1;
      else if (count >= 3 && count <= 5)
        div = 2;
    
      switch(div)
      {
          case 0:
             syear += s;
          break;
          
          case 1:
            smonth += s;
          break;
              
          case 2:
            sday += s;
          break;
      }
      count++;
   }
   
   year = strtoint(syear);
   month = strtoint(smonth);
   day = strtoint(sday);
   
   std::cout << "Year " << year << " " << "Month " << month << " " << "Day " << day;
}