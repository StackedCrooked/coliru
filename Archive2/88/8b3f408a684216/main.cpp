#include <iostream>
#include <valarray>
#include <vector>
#include <cmath>
 using namespace std;
 bool operator<(std::vector<int> &a,int &b)
{   
    int rbool=0;
    int size=a.size();
     for(int i=0;i<size;i++)
     {
        if (a[i]<b)
        {rbool=1;break;}
     }
     return rbool;
}
int main()
{
    cout<<endl<<"sadfasdfasdf";
    std::vector<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
 int b=11;
 
 
  if (a<b)
  count << endl<<"a中没有比b大的数";
   //else
   //count << endl<<"a中有比b大的数";
   
   
   
  cout<<endl<<b;
    return 0;
}