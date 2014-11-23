/**********************************************************/
/*
             模块名称：year.cpp
    		 功能描述：这是一个万年历程序
			 创建人：
			 修改日期：
*/
#include<iostream>
#include<iomanip>
char *week[]={"Sunday","Monday","Tuesday","	Wednesday","Thursday","Friday","Saturday"};
using namespace std;
/***********************************************************/
/*
            函数名称：countdays
			功能描述：判断指定的年份是否为闰年以及每年的天数
			修改记录：
*/
int countdays(int year)
{
int flag,yeardays;
int alldays=0;
for(int i=1980;i<year;i++)
{
if(!(i%4)&&i%100)
flag=1;
else
flag=0;
if(flag)
yeardays=366;
else
yeardays=365;
alldays+=yeardays;
}
return alldays;
}
/************************************************************/
/*
            函数名称：monthdays
			功能描述：判断指定的年份每一个月的天数
			修改记录:
*/
int monthdays(int year,int month)//计算任一年每月的天数
{
int flag,days;
switch(month){
case 1:
case 3:
case 5:
case 7:
case 8:
case 10:
case 12:days=31;break;
case 4:
case 6:
case 9:
case 11:days=30;break;
case 2:
if(!(year%400))
flag=1;
else if(!(year%4)&&(year%100))
flag=1;
else
flag=0;
if(flag)
days=29;
else
days=28;
}
return days;
}
/****************************************************
/*
                  函数名称：fn1
				  功能描述：显示一年的日历
				  修改记录：
*/
void fn1()
{
int year,i,j,t,k;
cout<<"\n输入年份:";
cin>>year;
t=(countdays(year)%7+2)%7;
for(k=1;k<=12;k++)
{
cout<<k<<"月的年历如下:";
cout<<endl;
cout<<setw(6)<<"Sunday"<<setw(6)<<"Monday"<<setw(6)<<"Tuesday"<<setw(6)<<"Wednesday"<<setw(6)<<"Thursday"<<setw(6)<<"Friday"<<setw(6)<<"Saturday"<<endl;
for(i=1;i<=monthdays(year,k);i++)
{
if(i==1)
{
for(j=0;j<t;j++)
{
cout.width(6);
cout<<" ";
}
}
else
cout.setf(ios::right);
cout.width(6);
cout<<i;
if((i+t)%7==0)
cout<<endl;
}
t=(t+monthdays(year,k)%7)%7;
cout<<endl;
}
}
/************************************************
         函数名称：fn2
		 功能描述：显示一月的日历
		 修改记录：
*/
void fn2()
{
int year,month,wkday,daysfrom=0;
//year,month------------------年，月；
//wkday-----------------------该年元旦是星期几；
//daysfrom---------------------某月1日距离1月1日即元旦的天数，初值是0，靠累加而得
int mthdays[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
//mthdays[i]表示月份为i的那一个月的天数（若为闰年的话，2月份要增加1天）
cout<<"输入年份以及此年的元旦是星期几用（0~6）表示:";
cin>>year>>wkday;         //输入年份以及该年的元旦是星期几
cout<<"输入此年月份（1~12）:";
cin>>month;
cout<<setw(6)<<endl;
cout<<setw(6)<<"Sunday"<<setw(6)<<"MOnday"<<setw(6)<<"Tuesday"<<setw(6)<<"Wednesday"<<setw(6)<<"Thursday"<<setw(6)<<"Friday"<<setw(6)<<"Saturday"<<endl;
int i,ans;
for(i=1;i<month;i++)
daysfrom+=mthdays[i];
if(month>2)
if((year%4==0)&&(year%100!=0)||(year%400==0))
daysfrom+=1;
ans=(wkday+daysfrom)%7;
cout<<setw(15)<<year<<"."<<setw(1)<<month<<setw(1)<<"."<<1<<setw(3)<<week[ans]<<endl;
cout<<"-------------------------"<<endl;
int wday=ans;
cout<<setw(6*(wday+1))<<1;
for(i=2;i<=mthdays[month];i++)
{
wday++;
if(wday%7==0)
{
cout<<endl;
wday=0;
}
cout<<setw(6)<<i;
}
cout<<"--------------------"<<endl;
}
/*******************************************************
/*
            函数名称：fn3
			功能描述：显示某一天是星期几
			修改记录：
*/
void fn3()
{
int year,month,data,w;
cout<<"\n输入年份:";
cin>>year;
cout<<"\n输入月份（1~12）:";
cin>>month;
cout<<"\n输入此年此月相应的日期（1~28|29|30|31）:";
cin>>data;
//下面的4条语句用来计算输入日期的星期数
w=year>0?(5+(year+1)+(year-1)/4-(year-1)/100+(year-1)/400)%7
:(5+year+year/4-year/100+year/400)%7;
w=month>2?(w+2*(month+1)+3*(month+1)/5)%7
:(w+2*(month+2)+3*(month+2)/5)%7;
if(((year%4==0&&year%100!=0)||year%400==0)&&month>2)
{
w=(w+1)%7;
}
w=(w+data)%7;
cout<<"\n该天是:"<<week[w];
cout<<endl;
}
/******************************************************

/*
             函数名称：main
			 功能描述：主程序
			 修改记录：
*/
void main()
{
int i=1;
cout<<endl<<endl;
cout<<"--------------------------------------"<<endl;
cout<<"*                                     *"<<endl;
cout<<"     欢迎进入万年历查询系统           "<<endl;
cout<<"*                                     *"<<endl;
cout<<"---------------------------------------"<<endl;
while(i)
{
cout<<endl<<endl;
cout<<"请选择您的查询内容:"<<endl<<endl;
cout<<"                1.显示一年的日历;"<<endl;
cout<<"                2.显示一月的日历;"<<endl;
cout<<"                3.显示某一天是星期几;"<<endl;
cout<<"请选择按键(0-3):";
cin>>i;
cout<<endl;
if(i>=0&&i<=3)
{switch(i)
{
case 1:fn1();break;
case 2:fn2();break;
case 3:fn3();break;
}
}
else
cout<<"按键错误，请重新选择！"<<endl;
cout<<endl;
}
}
