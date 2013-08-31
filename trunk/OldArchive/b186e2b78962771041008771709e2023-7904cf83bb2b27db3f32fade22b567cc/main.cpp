#include <cstdlib>
#include <iostream>

using namespace std;
int fnctn(int k)
{   int sum=1;
    for(int i=1; i<=k; i++)
    {
        sum*=2;
    }
    if(k==0)
        return 1;
    else
        return sum;
}
int main(int argc, char *argv[])
{   int k=0,j=1,y=0,x1,x;
    cout<<"enter binary no";
    cin>>x;
    x1=x;
    while(x>=1)
    {   while(x>1)
        {   k++;
            j*10;
            x=x/10;
        }
        y+=x*fnctn(k);
        k=0;
        x1=x1-(x*j);
        j=1;
        x=x1;
    }
    cout<<"in decimal system"<<y;
    system("PAUSE");
    return EXIT_SUCCESS;
}
