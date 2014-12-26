#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <iomanip>
using namespace std;

void function(double tmp);

int main()
{
    double tmp;
    cout<<" alpha1-alpha|"<<"   alpha|"<<"    x1  "<<"|      s   | "<<" dalpha1/de"<<" |      A3"<<"    |    dalpha1 |"<<"\t"<<endl;
    cout<<"_____________|________|________|__________|_____________|____________|____________|"<<endl;
    tmp=6*atan(1)*4/180;
    function(tmp);
    tmp=8*atan(1)*4/180;
    function(tmp);
    tmp=10*atan(1)*4/180;
    function(tmp);
    tmp=12*atan(1)*4/180;
    function(tmp);
    tmp=14*atan(1)*4/180;
    function(tmp);
    tmp=16*atan(1)*4/180;
    function(tmp);
    tmp=17.459*atan(1)*4/180;
    function(tmp);
    return 0;
}

void function(double tmp)
{
    double x,y;
    double x1;
    double alpha1;
    double alpha;
    double s;
    double dade;
    double w;
    double A3;
    double z;
    double dalpha1;
    x=1./6;
// cout«"x1= "«x«endl;
    x*=2-cos(tmp);
// cout«"x2= "«x«endl;
    x/=sin(tmp);
// cout«"x3= "«x«endl;
    y=12*sin(tmp)*sin(tmp);
    y/=(2-cos(tmp))*(2-cos(tmp));
// cout«"y1= "«y«endl;
    y=1-y;
// cout«"y2= "«y«endl;
    y=sqrt(y);
// cout«"y3= "«y«endl;
    y+=1;
// cout«"y4= "«y«endl;
    x*=y;
// cut«"x4= "«x«endl;
    x=1./x;
// cout«"x5= "«x«endl;
    x=atan(x);
// cout«"x6= "«x«endl;
//alpha=atan((1/6)*((2-cos(tmp))/sin(tmp))*(1+sqrt(1-(12*(sin(tmp)*sin(tmp))/((2-(cos(tmp)*cos(tmp)))*(2-(cos(tmp)*cos(tmp)))))));
    alpha=x;
//    cout<<"alpha= "<<x*180/(atan(1)*4)<<endl;  
    alpha1=alpha+tmp;
    x1=acos(sqrt(1./tan(alpha)*sin(tmp)))-alpha;
//    cout<<"x1= "<<x1*180/(atan(1)*4)<<endl;
    s=sin(alpha+x1)*sin(tmp/2)/cos(x1+alpha/2+alpha1/2);
//    cout<<"s= "<<s<<endl;
    x=atan(1)*4-alpha-alpha1-2*x1;
    w=s*s+(1+2*s)*sin(alpha+x1)*sin(alpha+x1);
    dade=-2*s*tan(x/2)*(s+sin(alpha+x1)*sin(alpha+x1))/w;
//    cout<<"dalpha1/de= "<<dade<<endl;
    y=tan(alpha);
//    cout<<"y0= "<<y<<endl;
    y=1./tan(alpha);
//    cout<<"y01= "<<y<<endl;
    y=y*y;
//    cout<<"y1= "<<y<<endl;
    x=tan(alpha+x1);
//    cout<<"x01= "<<x<<endl;
    x=tan(alpha+x1)*tan(alpha+x1);
//    cout<<"x1= "<<x<<endl;
    y=(1./tan(alpha))*(1./tan(alpha))*(tan(alpha+x1)*tan(alpha+x1));
//    cout<<"y1= "<<y<<endl;
    y=1-y;
//    cout<<"y2= "<<y<<endl;
    y*=1+3*tan(alpha)*tan(alpha);
//    cout<<"y3= "<<y<<endl;
//    cout<<"alpha= "<<alpha<<endl;
//    cout<<"x1_= "<<x1<<endl;
    z=cos(alpha+x1);
//    cout<<"z1= "<<z<<endl;
    z=z*z*z*z;
//    cout<<"z2= "<<z<<endl;
    z=1./z;
//    cout<<"z= "<<z<<endl;
    x=((1./tan(alpha))*(1./tan(alpha)))/(cos(alpha+x1)*cos(alpha+x1)*cos(alpha+x1)*cos(alpha+x1));
//    cout<<"x1= "<<x<<endl;
    x*=3*cos(tmp)*cos(2*(alpha+x1))+cos(2*tmp)+2*cos(alpha+x1)*cos(alpha+x1);
//    cout<<"x2= "<<x<<endl;
    A3=(1./6)*(y-x);
//    cout<<"A3= "<<A3<<endl;
    dalpha1=A3*((4./180)*atan(1)*4)*((4./180)*atan(1)*4)*((4./180)*atan(1)*4)*(45./atan(1));
//    cout<<"dalpha1= "<<dalpha1<<endl;
//    cout<<"alpha1-alpha "<<"alpha "<<"x1 "<<"s "<<"dalpha1/de "<<"A3 "<<"dalpha1 ";
    cout<<setw(12)<<tmp*45/atan(1)<<" | "<<setw(7)<<alpha*45/atan(1)<<"| "<<setw(7)<<x1*45/atan(1)<<"| "<<setw(9)<<s<<"| "<<setw(10)<<dade<<"  | "<<setw(11)<<A3<<"| "<<setw(11)<<dalpha1*45/atan(1)<<"|"<<"\t\v"<<endl;
}