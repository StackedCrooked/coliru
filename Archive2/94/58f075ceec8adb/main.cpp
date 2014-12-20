#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

void visualizza(int v[])
{
     int x;
     cout<<v[x]<<"\t";
     if (v[x]==10||v[x]==20||v[x]==30||v[x]==40||v[x]==50||v[x]==60||v[x]==70||v[x]==80)
            cout<<"\n\n";
}

void visualizza1(int v[])
{
     int x;
     cout<<"["<<v[x]<<"]\t";
     if (v[x]==10||v[x]==20||v[x]==30||v[x]==40||v[x]==50||v[x]==60||v[x]==70||v[x]==80)
            cout<<"\n\n";
}

void carica(int v[])
{
    int s=1;
    for (int x=0;x<90;x++)
    {
        v[x]=s;
        s++;
        visualizza(v);
    }
}

void ricerca(int v[],int num)
{
    for (int x=0;x<90;x++)
    {
        if (v[x]!=num)
        {
            visualizza(v);
        }
        else
        {
            visualizza1(v);
        }
    }
}

int main()
{
    srand((unsigned)time(NULL));
    int v[90],num;
    cin.get();
    carica(v);
    num=(rand()%90)+1;
    ricerca(v,num);
    return 0;
}
