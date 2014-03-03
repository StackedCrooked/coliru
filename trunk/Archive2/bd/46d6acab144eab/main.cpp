// HelloWorld.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

//#include "stdafx.h" // Diese Datei wird zum Erstellen der vorkompilierten Headerdatei "Win32.pc" und der vorkompilierten Typendatei "StdAfx.obj" verwendet
#include <stdlib.h> // Die Definitionsdatei <stdlib.h> vereinbart Funktionen zur Umwandlung von Zahlen, für Speicherverwaltung und ähnliche Aufgaben. 
#include <stdio.h> // Die Ein- und Ausgabefunktionen, Typen und Makros, die in <stdio.h> vereinbart sind, machen nahezu ein Drittel der Bibliothek aus. 
#include <string.h> // In der Definitionsdatei <string.h> werden zwei Gruppen von Funktionen für Zeichenketten vereinbart. Die erste Gruppe hat Namen, die mit str beginnen; die Namen der zweiten Gruppe beginnen mit mem. Sieht man von memmove ab, ist der Effekt der Funktionen undefiniert, wenn zwischen überlappenden Objekten kopiert wird. 
#include <math.h> // math.h ist eine Header-Datei in der Standard C Library der Programmiersprache C
//#include <conio.h> // Deklariert verschiedene Funktionen, die für den Aufruf der Textbildschirm-Ein-/Ausgabe-Routinen des Betriebssystems verwendet werden. 
#include <time.h> // Definiert Strukturen und Funktionen zum Umgang mit Datum und Zeit

int main(int argc, char ** argv) //automatische ausgeführte Hauptfunktion

{ 
    //Variablen werden deklariert:
    double a=0;
	double b=0;
	double ergebnis=0;
	char auswahl=0;

	while(1) //einfache Schleife (solange die Bedingung erfüllt ist)
	{
		printf("Waehlen Sie eine Rechenoperation\n\n"); 
		printf("(A)ddition,(S)ubtraktion, (M)ultiplikation, (D)ivision\n\n");
		scanf("%c",&auswahl); //entweder diesen Befehl für Ausgabe oder der u.g.
		//auswahl=getch();

		switch (auswahl) {
			case 'a':
			case 'A':
				printf("Addition wurde gewaehlt\n\n");
				break;
			case 's':
			case 'S':
				printf("Subtraktion wurde gewaehlt\n\n");
				break;
			case 'm':
			case 'M':
				printf("Multiplikation wurde gewaehlt\n\n");
				break;
			case 'd':
			case 'D':
				printf("Division wurde gewaehlt\n\n");
				break;
			default:
				printf("Falsche Auswahl");
				break;
		}

		printf("Zahl1 ? ");
		scanf("%lf",&a);
		fflush(stdin);

		printf("Zahl2 ? ");
		scanf("%lf",&b);
		fflush(stdin);

		switch (auswahl) {
			case 'a':
			case 'A':
				ergebnis=a+b;
				break;
			case 's':
			case 'S':
				ergebnis=a-b;
				break;
			case 'm':
			case 'M':
				ergebnis=a*b;
				break;
			case 'd':
			case 'D':
				ergebnis=a/b;
				break;
		}

		printf("Ergebnis: %.2f\n\n",ergebnis);

		//system("pause");
	}
	return 0;
}