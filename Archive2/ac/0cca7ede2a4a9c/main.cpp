#include <iostream>
 #include <math.h>
 // 2.2- Inclusion des directives spéciales 
using namespace std ; 
int main()
 {
 // declaration variables
 int continuer ;
 int a,b,c,x,x1; 
cout << "BIENVENUE DANS MON PROGRAMME"<<endl;
 cout << endl << "1- Continuer 2- Quitter " << endl; 
cout << "Reponse : ";
 cin >> continuer;
 while(continuer == 1)
 {
 cout << endl << "Veuillez entrer la valeur de a : "; 
cin >> a;
 cout << "Veuillez entrer la valeur de b : ";
 cin >> b;
 cout << "Veuillez entrer la valeur de c : ";
 cin >> c;
 x1=b*b-(4*a*c); 
if (x1 > 0)
 {
 cout << "La valeur de x1 est" << (-b+sqrt(x1)/2*a) << endl;
 cout << "La valeur de x2 est" << (-b-sqrt(x1)/2*a) << endl;
 }
 else if (x1==0) { cout << "La valeur de x1 est" <<(-b/2*a) <<endl ;
 } 
else
 { 

 cout << " x1 est " << (-b/(2*a)) << " + i" <<(-b+sqrt(fabs(b*b-4*a*c)))/(2*a) << "\n";
 cout << " x2 est " << (-b/(2*a)) << " - i" <<(-b+sqrt(fabs(b*b-4*a*c)))/(2*a) << "\n"; 
} 
cout << "Avez-vous d'autres équations à vérifier' ? "; 
cout << "Si oui, appuyer sur 1. Si non, appuyer sur 2. \n";
 cin >> continuer;
return 0;
 }
 }