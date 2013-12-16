#include <stdio.h>

void fecha(int,int);
int valid_date(int,int,int);//Prototype
int bisiesto (int); //Prototype
int sum_day(int,int,int,int);
/////////////////////////////////////////////////////////////////////////////
int main()
{
   int date= 20160219U;
   int day = 15U;
  
   fecha(date,day);   
}
/////////////////////////////////////////////////////////////////////////////
void fecha( int date,int day)
{    
    int yy = date/10000;
    int mm = (date/100)%100;
    int dd = date%100;
    
    sum_day(dd,mm,yy,day);
   
    if(valid_date(dd,mm,yy)==1)
    {
        printf("Day   : ");        
        printf("%d\n",dd);                
        printf("Month : ");
    
    switch(mm)
    {
        case 1:printf("Enero\n");
               break; 
        case 2:printf("Febrero\n");
               break;
        case 3:printf("Marzo\n");
               break;
        case 4:printf("Abril\n");
               break;
        case 5:printf("Mayo\n");
               break;
        case 6:printf("Junio\n");
               break;
        case 7:printf("Julio\n");
               break;
        case 8:printf("Agosto\n");
               break;  
        case 9:printf("Septiembre\n");
               break;
        case 10:printf("Octubre\n");
               break;
        case 11:printf("Noviembre\n");
               break;
        case 12:printf("Diciembre\n");
               break;
        default: printf("Mes Invalido\n");
                     
    }        
    printf("Year  : ");
    printf("%d\n",yy);   
    }
    else
    {
         printf("La fecha ingreasa es invalida\n");        
    }
}


int valid_date(int dd,int mm,int yy)
{
    int maxd=0;
    
    switch(mm)
    {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            maxd=31;
            
            break;
        case 4: case 6: case 9: case 11:
            maxd=30;
            break;
        case 2:
            maxd= bisiesto(yy)? 29:28;
            break ;
        default:
            return 0;        
    }
    return dd>=1 && dd<=maxd;
}


int bisiesto (int yy)
{
    if(yy%400==0)
        return 1;
    if(!(yy%100))
        return 0;
    return !(yy%4);
}

int sum_day(int dd,int mm,int yy,int day)
{        
   
   int maxd=0;
   int val=0;     
   dd=dd+day;
   val=dd;
   do
   {
    
        switch(mm)
        {
            case 1: case 3: case 5: case 7: case 8: case 10: case 12:
                maxd=31;            
                break;
            case 4: case 6: case 9: case 11:
                maxd=30;
                break;
            case 2:
                maxd= bisiesto(yy)? 29:28;
                break ;  
        }        
        
        if(val<=maxd)
            val =0;
        else
        {
            dd=dd-maxd;
            mm++;
            if(mm==13)
            {
                yy++;
                mm=01;
            }
        }
    }while(val!=0);
    
    printf("%d\n",dd);
    printf("%d\n",mm);
    printf("%d\n",yy);      
    
}











