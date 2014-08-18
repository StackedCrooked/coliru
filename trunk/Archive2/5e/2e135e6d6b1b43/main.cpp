#include <iostream>
#include <string>
#include <vector>

  using namespace std;
  int main()
  
  {
      double hours=0;
      double rph=0;
      double tax=0;
      double networth=0;
      
      cout<<"Enter No. of Hours Worked:"<<endl;
      cin>>hours;
      
       cout<<"Rate per Hour:"<<endl;
      cin>>rph;
      
       cout<<"Enter Amount of Tax:"<<endl;
      cin>>tax;
      
      networth= hours * rph - tax;
      
       cout<<"Your Networth is:"<<endl;
     cin>>networth;
     
     
     return 0;
     
  }
      
      
      
      
     
        