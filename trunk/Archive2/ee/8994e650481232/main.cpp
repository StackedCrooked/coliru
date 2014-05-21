//auotofficina.cpp:bmw
#include<iostream>
#include<string>
using namespace std;
int main ()
{
    int n,spesa,conta;
    string x;
    spesa=0;
cout<<"                             AUTOFFICINA MACERA"<<endl;
cout<<" "<<endl;
cout<<"BENVENUTO"<<endl;
cout<<" "<<endl;
cout<<"Scelga tra le varie opzioni il lavoro da effttuare,e il numero di lavori"<<endl;
cout<<" "<<endl;
cout<<"                                               *Costo ora lavorativa=20"<<endl;
cout<<" "<<endl;
cout<<"    A)[Tagliando]..................prezzo=200   ore lavorative=24"<<endl;
cout<<"    B)[Riparazione carrozzeria]....prezzo=1000  ore lavorative=15"<<endl;
cout<<"    C)[Ricambio pasticche].........prezzo=50    ore lavorative=4"<<endl;
cout<<"    D)[Ricambio armortizzatori]....prezzo=400   ore lavorative=10"<<endl;
cout<<"    E)[Ricambio filtri]............prezzo=100   ore lavorative=5"<<endl;
cout<<"    F)[Ricambio fari]..............prezzo=300   ore lavorative=3"<<endl;
cout<<" "<<endl;
cout<<"Quanti lavori bisogna effettuare?"<<endl;
cin>>n;
do{
       conta=conta+1;
       cout<<"Iserisci il ";
       cout<<conta;
       cout<<") lavoro"<<endl;
       cin>>x;
       if(x=="a")
       spesa=spesa+680;
       if(x=="b")
       spesa=spesa+1360;
       if(x=="c")
       spesa=spesa+130;
       if(x=="d")
       spesa=spesa+600;
       if(x=="e")
       spesa=spesa+200;
       if(x=="f")
       spesa=spesa+360;
}while(n!=conta);
cout<<"La spesa  totale e' di ";
cout<<spesa;
cout<<" euro"<<endl;
cout<<" "<<endl;
cout<<"ARRIVEDERCI"<<endl;
cout<<" "<<endl;
system("pause");
return 0;
}
       
