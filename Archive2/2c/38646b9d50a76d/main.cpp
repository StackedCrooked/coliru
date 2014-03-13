#include <iostream>
#include <fstream>
#include <cmath>
#include <stdlib.h>//para todo lo de los número aleatorios
#include <time.h>//para la semilla

using namespace std;

int main(){
    //generar los números aleatorios que llamo a
    ofstream fs("histograma.dat"); 
    int n,i=0;   
    double a,b;
    double P,y;
    double Ptest;
    cout<<"numero de valores:"<<endl;
    cin>>n;
    
    //double porque deben ser valores reales no enteros
    srand(time(NULL));//semilla
    do { //es la secuencia de 100
    b=rand();
    a=(b*1.0/RAND_MAX*1.0)*6-2;//rango, divido rand/RAND_MAX para limitar los valores 0 Y 1, pero como quiero que el rango sea entre -2 y 4 por eso multiplico por 6 y resto 2 
    y=rand();
    Ptest=y/RAND_MAX;
    //calculo la probabilidad (Pa) y condicion para quedarme con los números
    P=exp(-pow(a-1,2));
    if(P>Ptest){
    cout<<a<<endl;
    fs<<a<<endl;
    i++;
    }}
    
    while(i<n);
    fs.close(); 
      
return 0; 
}
