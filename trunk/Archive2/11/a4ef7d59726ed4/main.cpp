/* Il mio primo programma */ 
 #include <cstdlib> 
 #include <iostream> 
 using namespace std; 
 int main(int argc, char *argv[]) 
 { 
 float x,y; // Variabili in Output 
 float risultato; // Variabili in Input 
 cout<<"Fare la somma di due numeri"<<endl; 
 cout<<endl; 
 cout<<"Indica il primo valore: "; 
 cin>>x; 
 cout<<"Indica il secondo valore: "; 
 cin>>y; 

 risultato=x+y; 

 cout<<"Risultato : "<<risultato <<endl; 

 system("PAUSE"); 
 return EXIT_SUCCESS; 
 } 
