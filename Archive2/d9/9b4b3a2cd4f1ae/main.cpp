#include<iostream>
using namespace std;
int main (){
    int numdinum;
    float max = 0;
    int cont = 0;
    float numero;
    
    cout<<"Inserire la quantità di numeri da confrontare"<<endl;
    cin>>numdinum;
while (cont<numdinum) {
cout<<"inserire il numero"<<endl;
cin>>numero;
        if (numero>max){
        max = numero;
        cont = cont+1;   }
        else{
        cont = cont+1;}
                
cout<<"il numero massimo inserito è "<<max<<endl;}
system ("pause");
return(0);}
