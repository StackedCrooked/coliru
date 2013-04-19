#include <cstdlib>
#include <iostream>
#include <string.h>
 
using namespace std;
 	
int main(int argc, char *argv[])
{
    int n, na,ne,qi,nq,nqf;
    string palabra;
 
    cout<<"Ingrese el numero de simbolos del Alfabeto: ";
    cin>>na;
 
    char alfabeto[na];
 
    for(int i=0;i<na;i++){
        cout<<"Ingrese el simbolo "<<i+1<<" : ";
        cin>>alfabeto[i];
    }
 
    cout<<"Ingrese el numero de estados: ";
    cin>>nq;
 
    cout<<"Ingrese el numero del estado inicial: ";
    cin>>qi;
 
    cout<<"Ingrese el numero de estados finales: ";
    cin>>nqf;
 
    int qf[nqf];
 
    for(int i=0;i<nqf;i++){
        cout<<"Ingrese el "<<i+1<<" estado final: ";
        cin>>qf[i];
    }
 
    int transiciones[nq][na];
 
    for(int i=0;i<nq;i++){
        for(int j=0;j<na;j++){
            cout<<"d(q"<<i<<","<<alfabeto[j]<<"):";
            cin>>transiciones[i][j];
        }
    }
 
    cout<<"t";
    for(int i=0; i<na;i++){
        cout<<"t"<<alfabeto[i];
    }
    cout<<endl;
 
    for(int i=0;i<nq;i++){
        cout<<"tq"<<i;
        for(int j=0;j<na;j++){
            cout<<"t"<<transiciones[i][j];
        }
        cout<<endl;
    }
    inicio:
    cout<<"Ingrese la palabra a analizar: ";
    cin>>palabra;
 
    n = palabra.length();
    int ea = qi;
    bool band=true;
 
    for(int i=0;i<n;i++){
        for(int j=0;j<na;j++){
            if(palabra[i]==alfabeto[j]){
                cout<<"d(q"<<ea<<","<<palabra[i]<<")= ";
                ea = transiciones[ea][j];
                cout<<"q"<<ea<<endl;
                if (ea==-1){
                    cout<<"Palabra rechazada"<<endl;
                    system("PAUSE");
                    goto inicio;
                }
            }
        }
    }
 
    for(int i=0;i<nqf;i++){
        if(ea==qf[i])
            cout<<"Palabra aceptada"<<endl;
            system("PAUSE");
            goto inicio;
    }
 
    cout<<"Palabra rechazada";
    system("PAUSE");
    goto inicio;
}