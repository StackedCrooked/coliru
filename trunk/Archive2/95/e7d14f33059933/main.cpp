#include <iostream>
using namespace std;

int main(){
	int scelta, punteggio,i;
	int giudice[5];
	cout<<"Dimmi cosa vuoi fare? 1.Toro 2.Torello 3.Puledro";
	cin>>scelta;
	
	switch(scelta){
		case 1:
			for(i=0; i<5;i++)
			{
				cout<<"Dammi voto del giudice";
				cin>>giudice[i];
			}break;
		case 2:
			for(i=0; i<5;i++)
			{
				cout<<"Dammi voto del giudice";
				cin>>giudice[i];
			}break;	
		case 3:
			for(i=0; i<5;i++)
			{
				cout<<"Dammi voto del giudice";
				cin>>giudice[i];
			}break;
	}
return 0;	
}