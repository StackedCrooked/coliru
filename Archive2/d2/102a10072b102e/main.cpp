#include <iostream>
using namespace std;
int main()
{
 int n;
 float V,TOTAL1,TOTAL2;
 int r1,r2,r3,r4,i;
 cout << "Give r1: ";//Im asking for resitors.
 cin >> r1;
 cout << "Give r2: ";
 cin >> r2;
 cout << "Give r3: ";
 cin >> r3;
 cout << "Give r4: ";
 cin >> r4;
 cout << "Give voltage: ";
 cin >> V;
 cout << "Give number of resistors: ";
 cin >> n;
   int a,b;//I try to count the number on its category.
 for(i=1;i<n+1;i++)
{
  float value;
  int m;
  m=0;
  m=m+1;
  cout << "Give resistane: ";
  cin >> value;

  a=0;
  b=0;
  if((value>=r1) && (value>=r2) && (value<=r3) && (value<=r4))
  {
   if(m%2>0)
   {
    cout << "It belongs to the first";
    a=a+1;
    TOTAL1=value+TOTAL1;//If they are in the first category they are connected in series
   }
    else
   {
     cout << "It belongs to the second";
     b=b+1;
     TOTAL2=1/value + 1/TOTAL2;
    }
  }
  else if((value>=r1)&&(value<=r2)){
  cout << "It belongs to the first";
  a=a+1;
  TOTAL1=value+TOTAL1;}
  else if((value>=r3)&&(value<=r4)) {
  cout << "It belongs to the second";
  b=b+1;
  TOTAL2=1/value + 1/TOTAL2;
  }
 }
 cout << "\n The first category has: "<< a;
 cout << "\n The second category has: " <<b; 
 cout << "\n The yotal resistance of the first category is: " << TOTAL1; 
 cout << "\n The total resistance of the second category is: " <<  1/(1/TOTAL2); 
 return 0;
}      