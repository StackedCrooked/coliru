#include <cstring>

class MitCopyKonstruktor
{
private:
  char *cString;
 
public:
  // gewöhnlicher Konstruktor
  explicit MitCopyKonstruktor(const char* value) 
  {
    cString = new char[strlen(value) + 1]; // Speicher der richtigen Länge reservieren
    strcpy(cString, value);  // Den String aus value in den reservierten Speicher kopieren
  }
 
  // Kopierkonstruktor:
  // hat in C++ immer die Signatur "Klassenname(const Klassenname&)"
  MitCopyKonstruktor(const MitCopyKonstruktor& rhs) // Üblicherweise rhs: "Right Hand Side"
  {
    cString = new char[strlen(rhs.cString) + 1];
    strcpy(cString, rhs.cString);
  }
};

int main()
{
MitCopyKonstruktor mitCC("Dulz");    // Erstellt eine Zeichenkette 
MitCopyKonstruktor mitCC2 = mitCC;  // Kopierkonstruktor, Zuweisungssyntax
MitCopyKonstruktor mitCC3(mitCC);    // Kopierkonstruktor, Aufrufsyntax
}