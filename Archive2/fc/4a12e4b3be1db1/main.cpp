#include <iostream>
using namespace std;
int main ()
{
    int i,n,p;
    cout<<"inserisci il numero di cui vuoi la tabellina"<<endl;
    cin>>n;
    for (i=1; i<=10; i++)
    p=n*i;
    cout<<"la tabellina di "<<n<<"è"<<p<<endl;
    return 0;
}