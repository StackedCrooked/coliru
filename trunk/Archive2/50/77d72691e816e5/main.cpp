#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

using namespace std;

int main(void) 
{
    char *t2;	//- Pointer t2 erstellt uninitialisiert
	char t1=0;	//- char t1 erstellt inhalt = 0x00

	t2=&t1;		//- t2 auf t1 zeigen lassen

for( int i = 0; i < 100; i++ )
{ 
	t2+=1; 		//- Adresse von t2 eins weiter ( Nirwana )
	*t2=0; 		//- Nirwana überschreiben
    
    cout << "run: " << i << " -> "<< *t2 << "\n";
	//printf("adresse: %p\n",t2);
}
}
