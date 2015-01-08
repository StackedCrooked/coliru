#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cctype>
using namespace std;

/* L'agenzia viaggi GV - Grandi Viaggi vi commissiona l'implementazione della funzione
AssegnaVolo. */


 
 
 /*Tale funzione riceve due liste dinamiche, una riguardante i voli a disposizione,
con i campi data, ora, numero di volo, aeroporto origine, aeroporto destinazione, posti disponibili
per l’agenzia.*/
struct datiVolo{ //informazioni riguardanti i voli disponibili
	char data[11];
	char ora[6];
	unsigned int numVolo; //i numeri che vengono assegnati al numero di volo partono da 0
	char origine[50];
	char destinazione[50];
	unsigned int posti; //numeri che partono da 0 in poi
};

typedef struct nodoV{
	datiVolo dV;
	nodoV* next;
}* voliPtr;
	voliPtr head=NULL;
	voliPtr curr=NULL;
	voliPtr temp=NULL;

void inserimentoV(char date[11], char ore[6], int numV, char origin[50], char destination[50], int postidisp){
	voliPtr n = new nodoV;
	n->next = NULL;
	strcpy(n->dV.data, date);
	strcpy(n->dV.ora,ore);
	n->dV.numVolo=numV;
	strcpy(n->dV.origine,origin);
	strcpy(n->dV.destinazione,destination);
	n->dV.posti=postidisp;
	if(head != NULL){
		curr=head;
		while(curr->next!=NULL){
			curr=curr->next;
		}
		curr->next=n;
	}
	else{
		head=n;
	}
}

/*La seconda lista descrive i clienti che hanno acquistato un pacchetto vacanze, con i
campi nome, cognome, data partenza, luogo della vacanza, numero partecipanti, puntatore al
volo; quest’ultimo vale NULL se al cliente non è stato ancora assegnato un volo.*/

struct datiClienti{
	char nome[50];
	char cognome[50];
	char dataP[11];
	char luogo[50];
	unsigned int numeroPartecipanti;
	nodoV* v;
};

typedef struct nodoC{
	datiClienti dC;
	nodoC* next;
}* clientiPtr;
clientiPtr h=NULL;
clientiPtr c=NULL;
clientiPtr t=NULL;

void inserimentoC(char name[50], char surname[50], char partenza[11], char dest[50], int partecipanti){
	clientiPtr n = new nodoC;
	n->next = NULL;
	strcpy(n->dC.nome, name);
	strcpy(n->dC.cognome,surname);
	strcpy(n->dC.dataP,partenza);
	strcpy(n->dC.luogo,dest);
	n->dC.numeroPartecipanti=partecipanti;
	n->dC.v=NULL;
	if(h != NULL){
		c=h;
		while(c->next!=NULL){
			c=c->next;
		}
		c->next=n;
	}
	else{
		h=n;
	}
}
 
void AssegnaVolo(voliPtr volo, clientiPtr cliente) {

  voliPtr    ptrV;
  clientiPtr ptrC;
  
  /** La scelta fatta è stata quella di assegnare i voli ai clienti nell'ordine 
   *  con cui i clienti compaiono nella loro lista dinamica.
   *  Può accadere che due (o più) clienti con la stessa data di partenza e 
   *  luogo di destinazione, non vengano assegnati a nessun volo per  
   *  insufficienza di posti nella totalità di voli aventi la data del viaggio 
   *  e il luogo di destinazione voluti (con orari e numero di volo differenti).  
   */
  
  for (ptrV = volo; ptrV != NULL; ptrV = ptrV->next) {   
    if (ptrV->dV.posti > 0) {// questo controllo può essere omesso (è superfluo)
      for (ptrC = cliente; ptrC != NULL; ptrC = ptrC->next) {
	 if ( ptrC->dC.numeroPartecipanti > 0                    && 
	      strcmp(ptrC->dC.dataP, ptrV->dV.data) == 0         &&
	      strcmp(ptrC->dC.luogo, ptrV->dV.destinazione) == 0 &&  
	      ptrC->dC.numeroPartecipanti <= ptrV->dV.posti ) { 
      
	   ptrC->dC.v = ptrV; 
	   ptrV->dV.posti -= ptrC->dC.numeroPartecipanti;  
	 } // end if
      } // end for -- ptrC  	 
    } // end if 
  } // end for -- ptrV
	 
} // end AssegnaVolo

voliPtr ricercaV(char luogo[50], char date[11]){
	voliPtr c = NULL;
	curr = head;
	while(curr!= NULL && strcmp(curr->dV.destinazione, luogo)==1 && strcmp(curr->dV.data, date)==1)
	{
		curr=curr->next;
	}
	if(curr=NULL){
		cout << "Il volo richiesto non e' stato trovato nella lista dei voli." << endl;
	}
	else
	{
		c=curr;
		return c;
	}
}

clientiPtr ricercaC(char nome[50], char cognome[50]){
	clientiPtr punt = NULL;
	c = h;
	while(c!= NULL && strcmp(c->dC.nome, nome)==1 && strcmp(c->dC.cognome, cognome)==1)
	{
		c=c->next;
	}
	if(c=NULL){
		cout << "Il cliente richiesto non e' stato trovato nella lista." << endl;
	}
	else
	{
		punt=c;
		return punt;
	}
}


int main(int argc, char** argv) {
/** Le due liste: quella dei voli e quella dei clienti verranno riempite 
     * separatamente (per esempio in sequenza); 
     * con l'accortezza di assegnare il valore iniziale NULL all'attributo 
     * dC.v dei nodi della lista clienti. 
     * Poi, sempre nel main(), la chiamata al sottoprogramma AssegnaVolo(...)
     * avrà lo scopo di completare i dati nella lista clienti, sostituendo 
     * (dove possibile) il valore NULL dell'attributo dC.v di ogni nodo con 
     * l'indirizzo del nodo della lista dei voli che contiene i dati del volo 
     * aereo individuato.
     */ 
     int opzioni;
     char ris[3], risp[3], risposta[3];
     do{
     cout << "Quale operazione vuole effettuare:"<<endl<<"Premere 1 per l'inserimento nell'elenco dei voli "<<endl<<"Premere 2 per l'inserimento nell'elenco dei clienti"<<endl<<"Premere 3 per il assegnamento del volo al cliente "<<endl;
     cin >> opzioni;
     cout << endl;
	 switch(opzioni){
	 case 1: 	char date[11], ore[6], destination[50], origin[50];
	 			int numV, postidisp;
     			cout << "----Registrazione dei voli----" <<endl;
     			do{
	 			cout << "Inserisci data di partenza nel formato gg/mm/aaaa" <<endl;
	 			cin >> date[11];
	 			cout << "Inserisci ora di partenza nel formato hh:mm" <<endl;
	 			cin >> ore[6];
	 			cout << "Inserisci il numero di volo" <<endl;
	 			cin >> numV;
	 			cout << "Inserisci il posto di partenza" <<endl;
	 			cin >> origin[50];
	 			cout << "Inserisci la destinazione del volo" <<endl;
	 			cin >> destination[50];
	 			cout << "Inserisci il numero di posti disponibili" <<endl;
	 			cin >> postidisp;
	 			inserimentoV(date, ore, numV, origin, destination, postidisp);
     			cout << "Vuole continuare l'inserimento? (si\no)" <<endl;
     			cin >>risp;
     			cout <<endl;
     			}while(risp=="si");
     			break;
     case 2: 
     			char name[50], surname[50], partenza[11], dest[50]; int partecipanti;
     			cout << "----Assegnazione dei voli ai clienti----" <<endl;
     			do{
     			cout << "Inserisci il nome del richiedente" <<endl;
	 			cin >> name[50];
	 			cout << "Inserisci il cognome" <<endl;
	 			cin >> surname[50];
	 			cout << "Inserisci la data di partenza nel formato gg/mm/aaaa" <<endl;
	 			cin >> partenza[11];
	 			cout << "Inserisci la destinazione" <<endl;
	 			cin >> dest[50];
	 			cout << "Inserisci il numero di partecipanti" <<endl;
	 			cin >> partecipanti;
	 			inserimentoC(name, surname, partenza, dest, partecipanti);	
     			cout << "Vuole continuare l'inserimento? (si\no)" <<endl;
     			cin >>ris;
				cout <<endl;	
     			}while(ris=="si");
     		break;
     case 3:
     	char nome[50], cognome[50], luogo[50], data[11];
     	voliPtr a; clientiPtr b;
     		cout << "Inserisci il nome del cliente al quale si vuole assegnare il volo" <<endl;
     		cin >> nome;
     		cout << "Inserisci il cognome del cliente al quale si vuole assegnare il volo" <<endl;
     		cin >> cognome;
     		cout << "Inserisci la destinazione" <<endl;
     		cin >> luogo;
     		cout << "Inserisci la data" <<endl;
     		cin >> data;
     	a=ricercaV(luogo, data);	
     	b=ricercaC(nome, cognome);
     	AssegnaVolo(a, b);
     	break;
     	
     default: 
     	cout << "L'opzione da lei scelta non si trova nell'elenco!" <<endl;
     	break;
	}
	 cout << "Torna indietro(si/no)?";
	 cin >> risposta;		
     			
 }while(risposta=="si");
     			
     			
     			
     			
     			
     			
     			
     
   
   return 0;
}
