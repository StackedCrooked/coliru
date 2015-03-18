#include<iostream>
#include<windows.h>
using namespace std;
class IN_TIME
{
    private:
    int hr;
    int min;
    int sec;
public:
IN_TIME()
{  hr=0;
min=0;
sec=0;
}

 IN_TIME(int a,int b,int c)
    {
       a=hr;
      b=min;
     c=sec;          
    }
Void settime(int h, int m, int s)
{
  h=hr;
m=min;
s=sec;
}
   
    void gettime()
{ cout<<”Enter hours:”;
cin>>hr;
cout<<”Enter minutes:”;
cin>>min;
cout<<”Enter seconds:”;
cin>>sec;
}
Void addtime()
{ if(sec>59)
 {min++;
sec=sec-60;}
elseif(min>59)
{hours++;
min=min-60;}
}
Void showtime()
{cout<<hr<<”:”<<min<<”:”<<sec;
}
};
Int main()
{ IN_TIME x;
x.gettime();
x.addtime();
x.showtime();
return 0;
}
