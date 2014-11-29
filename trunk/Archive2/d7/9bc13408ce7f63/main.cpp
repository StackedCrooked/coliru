#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

int main()
{
    char c;
    int count=0;
    while(scanf("%c", &c)>=1)
    {
        if(c=='\n')
        {
            cout<<c;
            count=0;
        }
        else if(c==',')
        {
            if(count==60)
            {
                cout<<endl<<c<<' ';
                count=2;
            }
            else if(count==59)
            {
                cout<<c<<endl<<' ';
                count=1;
            }
            else
            {
                cout<<c<<' ';
                count+=2;
            }
        }
        else
        {
            if(count==60)
            {
                cout<<endl<<c;
                count=1;
            }
            else
            {
                cout<<c;
                count++;
            }
        }
    }
    
    
    
    
    
   return 0;
}