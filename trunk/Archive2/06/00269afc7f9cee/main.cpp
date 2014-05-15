# include <iostream>
using namespace std;
int main()
{
    int i,c=1,n=5;
    for(i=2; i<n; i++)
    {
        c=n%i*c;
    }
    if (c==0)
        cout<<n<<"不是素数";
    else
        cout<<n<<"是素数";
}
