#include <iostream>
#include <math.h>

using std::cout;
using std::cin;
using std::endl;
using std::ostream;
using std::istream;

class Point;

unsigned short CalcDistance(const Point&,const Point&);

class Point
{
public:
 Point();
 Point(unsigned short);
 Point(unsigned short,unsigned short);

 unsigned short GetX() const { return cx; }
 unsigned short GetY() const { return cy; }

 void SetX(unsigned short x)   { cx=x; }
 void SetY(unsigned short y)   { cy=y; }

 Point& operator=(Point& rhs) { cx=rhs.GetX();
                                cy=rhs.GetY(); }

 friend ostream& operator<<(ostream&,Point&);
 friend istream& operator>>(istream&,Point&);
 
 friend unsigned short CalcDistance(const Point&,const Point&);
 
 virtual ~Point() { };
 
private:
 unsigned short cx,cy;

};

Point::Point():
    cx(0),
	cy(0)
{ }

Point::Point(unsigned short temp):
	cx(temp),
	cy(temp)
{ }

Point::Point(unsigned short x,unsigned short y):
	cx(x),
	cy(y)
{ }

int main(void)
{
 Point firstPoint,secondPoint;

 cout<<"Entrez les valeurs du premier point: ";
 cin>>firstPoint;
 cout<<endl;
 
 cout<<"Entrez les valeurs de second point: ";
 cin>>secondPoint;
 cout<<endl;
 
 cout<<"La distance entre les deux points est: "<<CalcDistance(firstPoint,secondPoint)<<endl;
 
 return 0;
}

unsigned short CalcDistance(const Point& firstPoint,const Point& secondPoint)
{
 unsigned short xa,ya,xb,yb;
 unsigned short distance=0;
 
 xa=firstPoint.cx;
 ya=firstPoint.cy;
 xb=secondPoint.cx;
 yb=secondPoint.cy;
 
 distance=sqrt( ((xa-xb)*(xa-xb))+((ya-yb)*(ya-yb)) );
 
 return distance;
}

ostream& operator<<(ostream& flux,Point& rhs)
{
 flux<<&rhs<<"'s x="<<rhs.cx<<endl;
 flux<<&rhs<<"'s y="<<rhs.cy<<endl;
 
 return flux;
}

istream& operator>>(istream& flux,Point& rhs)
{
 cout<<"x=";
 flux>>rhs.cx;
 cout<<endl;
 
 cout<<"y=";
 flux>>rhs.cy;
 cout<<endl;
 
 return flux;
}