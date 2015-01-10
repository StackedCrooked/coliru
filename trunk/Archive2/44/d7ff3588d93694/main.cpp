#include < iostream >
using namespace std; 
int main ( ){
    int x; 
    do {
        cout <<"Sei gay? Rispondi sinceramente. (inserisci il numero equivalente alla risposta)"<<endl;
        cout <<"1.Si\n2.No"<<endl;
        cin>> x;
        if (x==1)
          cout <<"Finalmente lo ammetti"<<endl;
        else if (x==2)
          cout <<"Ho detto rispondi sinceramente..."<<endl;
        else
        cout <<"Non hai inserito un numero corretto"<<endl;
    }
    while (x!=1);
return 0; 
}