#include <iostream>
using namespace std;

#include <string>

#include <iomanip>
using std::setw;

class Sekuence{
   public:
      Sekuence();  // Konstruktori
      ~Sekuence(); // Destruktori
      void inicializoTablen(void);
      void Insert( string vlera );
      void Delete( string vlera );
      bool Find( string vlera );
      void Print(void);
 
   private:
      string tabela[ 100 ];
};
 
//Konstruktori
Sekuence::Sekuence(void){
    inicializoTablen();
    cout << "Object po krijohet" << endl;
}

//Destruktori 
Sekuence::~Sekuence(void){
    cout << "Object po fshihet" << endl;
}

void Sekuence::inicializoTablen( ){
   for ( int i = 0; i < 100; i++ ){
      tabela[ i ] = "";
   }
}

void Sekuence::Insert( string vlera ){
   cout << "Duke shtuar elementin: " << vlera<< endl;
   int indeksi=-1; //indeksi se ku duhet te shtohet vlera e re
   for ( int i = 0; i < 100; i++ ){
   	//Shtoje vleren e re nqs duhet eshte e fundit
   	if(tabela[i].compare("")==0){
   	    tabela[i]=vlera;
   	      return;
   	}
   	if(tabela[i].compare(vlera)>0){
   	    indeksi=i;
   	    break;
   	}
   }
  
   //Sposto elementet me nje pozicion nga e djathta duke filluar nga fundi 
   for ( int j = 98; j >= indeksi; j-- ){
   	      tabela[j+1]=tabela[j];
   }
   
   //Vendos Vleren e re ne pozicionin qe duhet pa prishur renditjen
   tabela[indeksi]=vlera;   
   
}

void Sekuence::Delete( string vlera ){
   cout << "Duke fshire elementin: " << vlera<< endl;
   int indeksi=-1; //indeksi i elementit qe duhet fshire
   for ( int i = 0; i < 100; i++ ){
   	if(tabela[i].compare(vlera)==0){
   	    indeksi=i;
   	    break;
   	}
   }

   //Sposto elementet me nje pozicion nga e majta duke filluar nga elementi qe duhet fshire 
   for ( int j = indeksi; j < 99; j++ ){
   	      tabela[j]=tabela[j+1];
   }
}

bool Sekuence::Find( string vlera ){
   cout << "Duke kerkuar elementin: " << vlera<< endl;
   for ( int i = 0; i < 100; i++ ){
   	if(tabela[i].compare(vlera)==0){
   		cout << "Elementi u gjet."<< endl;
   	    return true; 	
   	}
   }
  cout << "Elementi nuk u gjet."<< endl;	
  return false; 
}

void Sekuence::Print(void){
   cout << "Elementi" << setw( 13 ) << "Vlera" << endl;
   // printo elementet jo bosh te tabeles                     
   for ( int i = 0; i < 100; i++ ){
   	if(tabela[ i ].compare("")!=0){
   	    cout << setw( 7 )<< i+1 << setw( 13 ) << tabela[ i ] << endl;	
   	}
   }
}

// Main function for the program
int main( ){
   Sekuence sekuence;
   
   sekuence.Insert("Genci");
   sekuence.Insert("Niku");
   sekuence.Insert("Geri");
   sekuence.Insert("Arber");
   sekuence.Insert("Ermal");
   sekuence.Insert("Eris");
   sekuence.Print();
   sekuence.Find("Arber");
   sekuence.Delete("Ermal");
   sekuence.Print();
   sekuence.Delete("Geri");
   sekuence.Print();
   return 0;
}