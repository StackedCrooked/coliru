#include <stdio.h>  
#include <stdlib.h>    
//判断年是不是闰年  
int isRunYear(int year)  
{  
    if((year%4==0&&year%100!=0)||year%400==0)  
        return 1;  
    else  
        return 0;  
}  
int main()  
{  
    int hour,minute,second,day,month,year;  
    int mhour,mmin,msec,mday,mmonth,myear;  
    //通过二维数组的方式存储月的情况，主要是闰年的2月和平年的2月  
 int dayofmonth[2][13]={{0,31,28,31,30,31,30,31,31,30,31,30},{0,31,29,31,
30,31,30,31,31,30,31,30}};  
    int n; 
    printf("输入时间的组数："); 
    scanf("%d",&n);  
    while(n--){
	printf("输入时:分:秒 日.月.年") ; 
scanf("%d:%d:%d %d.%d.%d",&hour,&minute,&second,&day,&month,&year);  
    if(year<2000||year>50000)  
    return 1;  
    int s=0;  
    int days=0;  
    days=days+(year-2000)*365;  
    int yy;  
    yy=year;  
    while(year>=2000)  
    {  
        int x=year-1;  
        if(isRunYear(x)==1)  
        days+=1;  
        year--;  
        }  
    int i;  
    for(i=0;i<month;i++){  
        days+=dayofmonth[isRunYear(yy)][i];  
    }  
  
    days+=day-1;  
    myear=days/1000;  
    days=days%1000;  
    mmonth=days/100+1;  
    mday=days%100+1;  
    s=(hour*3600+minute*60+second)*125/108;  
    mhour=s/10000;  
    s-=mhour*10000;  
    mmin=s/100;  
    msec=s-mmin*100; 
	printf("输出结果：");  
	printf("%d:%d:%d %d.%d.%d\n",mhour,mmin,msec,mday,mmonth,myear);    
}  
    return 0;  
}  