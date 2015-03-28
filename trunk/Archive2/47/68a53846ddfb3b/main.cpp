#include <iostream> 
#include <algorithm>    
using namespace std;

int main () {
    
  int w = 0; int d = 0; int o = 0; int t = 0; int g = 0; int l = 0; int e = 0; int c = 0; int m = 0; 
  int wwwdot = 0, google = 0, dotcom = 0;
  int myints[] = {1,2,3,4,5,6,7,8,9};

  //sort (myints,myints+9);
    wwwdot = w*100000 + w*10000 + w*1000 + d*100 + o*10 + t;
    google = g*100000 + o*10000 + o*1000 + g*100 + l*10 + e;
    dotcom = d*100000 + o*10000 + t*1000 + c*100 + o*10 + m;
  
  while ( next_permutation(myints,myints+9)) {   
   
    if (wwwdot - google == dotcom)

    {
    w=myints[0]; d=myints[1]; o=myints[2]; t=myints[3]; g=myints[4]; l=myints[5]; e=myints[6]; c=myints[7]; m=myints[8];}
   
  
  };
    
    
cout << wwwdot << '\n';
cout << google << '\n';
cout << dotcom << '\n';

 
    
    
 

}