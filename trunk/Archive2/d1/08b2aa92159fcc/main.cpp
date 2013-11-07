#include <iostream>
 
using namespace std;
 
// SUN: 0, MON:1, TUE:2, WED:3, THU:4, FRI:5, SAT:6 -> initialized with  int values starting from 0
typedef enum days {SUN, MON, TUE, WED, THU, FRI, SAT} days;
 
// operator +day adds a day 
inline days operator+(days d) {
   return static_cast<days>((static_cast<int>(d)+1)%7);
}
 
// adding an extra day using ++day operator - pass by reference (by copy does not update d)
inline days operator++(days& d) {
   // increment the d by one day using operator+
   d=+d;
   return d;
}
 
 
ostream& operator<< (ostream & out, days d) {
     switch (d) {
        case SUN: out << "SUN"; break;
        case MON: out << "MON"; break;
        case TUE: out << "TUE"; break;
        case WED: out << "WED"; break;
        case THU: out << "THU"; break;
        case FRI: out << "FRI"; break;
        case SAT: out << "SAT"; break;
     }
     
     return out;
}
 
int main() {
   days day={SAT};
 
   cout << day << endl;
 
   // using +day to update to next day
   for (int i=0; i<10; ++i) {
       // cout << +day << endl;
       // will not update to next day.. but this one will do it:
       day=+day;
       cout << day << endl;
   }
   cout << ".." <<  endl;
 
   // the ++day is updating the day to the next day 
   for (int i=0; i<10; ++i) {
       cout << ++day << endl;
   }
 
   return 0;
}