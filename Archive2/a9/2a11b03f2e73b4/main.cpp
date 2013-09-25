#include <iostream>
using namespace std;
 
const int n=4;
 
void saisir(int t[n]) 
{
    int i;
    for(i=0; i<n; i++) 
    {
        cout<<"Tapez la valeur numero "<<i<<" : ";
        cin >> t[i];
    }
} 
 
void affiche(int t[n]) 
{
    int i;
    for(i=0; i<n; i++) cout<<"La valeur numero "<<i<<" est : "<<t[i]<<endl;
}
 
int main()
{
    int a[n];
    saisir(a);
    affiche(a);
    return 0;
}
