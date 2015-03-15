#include <iostream>
using namespace std;

int main()
{
   int numero=0;
    int i=2;
    int c=1;
    
    //input dei dati
    cout<<"Inserisci un numero : " <<endl ;
    cin>>numero;
    
    //esculdiamo i casi in cui il numero sia '1' o '2'
    if(numero==1)
    {cout<<"Hai inserito un numero primo"<<endl;}
    else if (numero==2)
    {cout<<"Hai inserito un numero primo"<<endl;}
    
    while(i<=numero){
      i*=c;
      i++;
      if(i==numero)
      {  cout<<"Hai inserito un numero primo"<<endl; 
        //se il numero  èprimo 
        //blocchiamo il ciclo e il programma finisce            
        break;}
      
      if(numero%i==0){
         cout<<"Il numero inserito non è primo!"<<endl;
         //se il numero non è primo blocchiamo il programma
         break;             
      }
    }
    return 0;
}
