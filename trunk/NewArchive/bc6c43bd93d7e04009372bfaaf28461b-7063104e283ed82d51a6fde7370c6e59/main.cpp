#include <stdio.h>
//#include <conio.h> Für den Befehl getchar()
void berechneOstern(int pJahr, int *osterMonat, int *osterTag)
{
int varA = pJahr % 19;
int varB = pJahr % 4;
int varC = pJahr % 7;
int varK = pJahr / 100;
int varP = (8 * varK + 13) / 25;
int varQ = varK / 4;
int varM = (15 + varK - varP - varQ) % 30;
int varN = (4 + varK - varQ) % 7;
int varD = (19 * varA + varM) % 30;
int varE = (2 * varB + 4 * varC + 6 * varD + varN) % 7;
//Berechne Ostertag
*osterTag = (22 + varD + varE);
//Wenn der Tag größer als 31, bestimme Tag im April
if (*osterTag > 31) {
*osterTag -= 31;
*osterMonat = 4;
}
//Falls Tag kleiner 32, Monat ist März
else *osterMonat = 3;
}
int main()
{
int jahr, monat, tag;
if (scanf ( "%d" , &jahr ) == 0) {
return 1;
} // Ungültige Eingaben abfangen
berechneOstern(jahr, &monat, &tag);
printf( "%02d.%02d.%04d\n\n" , tag, monat, jahr);
return 0;
//getch(); Nur für Windows, damit Fenster bleibt
}
