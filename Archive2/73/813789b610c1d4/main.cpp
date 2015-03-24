#include <iostream>
#include <stdlib.h>
#include <iomanip>

using namespace std;
const int N=4;
void Bubble (int *VET, int N);

main()
{
  int vettore[N],i;
  cout<<"inserisci il vettore";
  for (i=0;i<N;i++){
      cin>>vettore[i];
  }
  Bubble(vettore, N);
  for (i=0;i<N;i++)
      cout<<vettore[i];
system ("PAUSE");
}

void Bubble (int *VET, int N){
    int sup, comodo, i;
    int continua;
    continua=1;
    while (continua=1){
        continua=0;
        for(i=0;i<N;i++){
            if (VET[i]>VET[i+1]){
                comodo=VET[i];
                VET[i]=VET[i+1];
                VET[i+1]=comodo;
                continua=1;
            }
        }
    }
}