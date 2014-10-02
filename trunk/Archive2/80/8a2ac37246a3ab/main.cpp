
#include <iostream.h>
#include <stdio.h>    	
#include <string.h> 
#include <math.h>		   			   

double somma(double, double);					
double sott(double, double);
double prodotto(double, double);
double divisione(double, double);
double inverso(double);
double radice(double);
double potenza (double n1, double n2);


int main()					
{
	double n, ris=0;
	char op;
	cout<<"ELENCO OPERAZIONI DISPONIBILI:\n"<<endl;
	cout<<"somma (+)"<<endl;			
	cout<<"sottrazione (-)"<<endl;
	cout<<"prodotto (*)"<<endl;
	cout<<"divisione (/)"<<endl;
	cout<<"inverso di un numero (!)"<<endl;
	cout<<"potenza (^)"<<endl;
	cout<<"radice quadrata (R)"<<endl;	
	cout<<"visualizzazione risultato (=)"<<endl;

	cout<<"\n\nPrimo numero: ";						
	cin>>ris;
	while (op!='='){
		cout<<"Operatore: ";
		cin>>op;
		switch (op)									
		{
		case '+': 
			cout<<"Secondo numero: ";
			cin>>n;	  
			ris=somma(ris,n);				
			break;
		case '-':
			cout<<"Secondo numero: ";
			cin>>n;   
			ris=sott(ris,n);			
		    	break;
		case '*': 
			cout<<"Secondo numero: ";
			cin>>n;
			ris=prodotto(ris,n); 
			break;					
		case '/': 
			cout<<"Secondo numero: ";
			cin>>n;
			ris=divisione(ris,n); 
			break;
		case '!': 
			ris=inverso(ris); 
			break;
		case '^': 
			cout<<"Secondo numero: ";
			cin>>n;
			while(ris==0 && n<0){
				cout<<"Errore! Reinserire il secondo numero (maggiore di 0)(In base alla scelta dei matematici): ";
				cin>>n;
			}
			ris=potenza(ris,n); 
			break;
		case 'R': 
			ris=radice(ris); 
			break;						
		case '=': 
			cout<<ris<<endl; 
			break;
	
		default: cout<<"operazione non possibile"<<endl; 
		}
	}
	getchar();
	return 0;
}


double somma(double n1, double n2)
{
	return n1+n2;
}

double sott(double n1, double n2){
	return n1-n2;
}

double prodotto(double n1, double n2)
{
	return n1*n2;
}
double divisione(double n1, double n2)
{
	return n1/n2;

}
double inverso(double n1)
{
	return n1*(-1);
}

double radice(double n1)
{
	return sqrt(n1);
}

double potenza (double n1, double n2)	
{
	double base, ris=1;
	if (n2>0) base=n1;
	else {
		base = (double)1/n1;
		n2 = -n2;
	}
	if (n2==0) return 1;
	else {
		for (int i=0; i<n2; i++) {
			ris*=base;
		}
		return ris;
	}
}