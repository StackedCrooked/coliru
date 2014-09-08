#include<iostream>
using namespace std;

int main()
{
    int table[3][4];
    int r,c,i;
    r=c=0;
    while(r<=2)
    {
        for(r=0;r<5;r++)
            cout<<"enter values in rows"<<endl;
        cin>>table[r][c];
    }
    r++
    for(i=0;i<5;i++)
    {
        cout<<table[r][c]<<"\t";
        cout<<endl;
    }
    getch();
}
