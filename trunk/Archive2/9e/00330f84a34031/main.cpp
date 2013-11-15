#ifndef TIME_H
#define TIME_H
using namespace std;
class time
{
private:
    int hour;
	int minute;
	int sceond;
		
public:
	    void settime(int h,int m,int s);
		void sethour(int h);
		
		void setminute(int m);
	
		void setsecond(int s);
		int gethour();
	
		int getminut();
	
		int getsceond();


};
#endif
#include<stdexcept>
#include"time.h"
#include<iomanip>
using namespace std;
time::time(int houre,int minut,int second)
{
    settime(houre,minut,second);

}
void time::settime(int h,int m,int s)
{
	sethour(h);
	setminut(m);
	setscond(s);
}
void time::sethour(int h)
{
	if(h>=0&&h<24)
	hour=h;
	else 
	throw invalid_argument("hour must be 0-23")  
}
void time::setminut(int m)
{	if(m>=0&&m<60)
    minut=m; 
	else 
	throw invalid_argument("minut must be 0-59")
}
void time::setscond(int s)
{	if(s>=0&&m<60)
    scond=s;
	else 
	throw invalid_argument("scond must be 0-59")
}
int time::getminut()
{
    return minut;
}
	int time::gethour()
	{
		return hour;
	}
	int time::getscond()
	{
		return scond;
	}
