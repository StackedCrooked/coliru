#include <iostream>
#include <cmath>
using namespace std;

int t[20];

void inserimento (int valore, int i=0){
    int s;
s=10;
cin>>valore;
do 
{cin >> t[i];
i++;
}while(i!=20);
}
int v[20];
void formula (int s) { 
    int i ;
i=0;
do{
    v[i]=s/t[i];
    cout<< v[i]<< endl;
    
}while (i!=20);
}
int main ()

{ int i,valore,s;
s=10;
    inserimento(valore,i=0);
    formula(s);
}

