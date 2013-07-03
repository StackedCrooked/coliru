#include <iostream>
#include <string>
#include <set>

using namespace std;

class Bauteil {
protected:
string name;
public:
Bauteil(){ name = "???"; cout << "Bauteil erzeugt" << endl; }
~Bauteil(){ cout << "Bauteil zerstoert" << endl;}
void zeigeName(){ cout << "Name: " << name << endl; }
};
class A : public Bauteil {
public:
A() { name = "A"; cout << name << " erstellt" << endl; }
~A(){ cout << name << " zerstoert" << endl; }
};
class B : public Bauteil {
public:
B() { name = "B"; cout << name << " erstellt" << endl; }
~B(){ cout << name << " zerstoert" << endl; }
void zeigeName(){ cout << "B-Teile" << endl; Bauteil::zeigeName(); }
};
class Baugruppe {
private:
set<Bauteil*> gruppe;
typedef set<Bauteil*>::iterator Iter;
public:
Baugruppe(){ cout << "Baugruppe erstellt" << endl; }
Baugruppe(const Baugruppe& other){ cout << "Baugruppe kopiert" << endl;
for(Iter i=other.gruppe.begin(); i != other.gruppe.end(); ++i){
gruppe.insert(*i);
}
}
virtual ~Baugruppe(){ cout << "Baugruppe zerstoert" << endl; }
void hinzufuegen(Bauteil* teil){ gruppe.insert(teil); }
void entfernen( Bauteil* teil){ gruppe.erase(teil); }
void zeigeElemente(){
cout << endl << "-------------------------";
cout << "\nBaugruppe bestueckt mit: " << endl;
for(Iter i = gruppe.begin(); i != gruppe.end(); ++i){
(*i)->zeigeName();
} cout << "-------------------------" << endl;
}
};

void anzeigen(Baugruppe gruppe){
gruppe.zeigeElemente();
 }
void test(){
Baugruppe gruppe1;

A* a1 = new A();
B* b1 = new B();
Bauteil* b2 = new B();



 gruppe1.hinzufuegen(a1);
 gruppe1.hinzufuegen(b1);
 gruppe1.hinzufuegen(b2);

 anzeigen(gruppe1);

 b1->zeigeName();

 Baugruppe gruppe2 = gruppe1;
 A a2;
 gruppe2.hinzufuegen(&a2);
 gruppe2.zeigeElemente();
delete b1;
delete b2;

 }

int main(){
 test();
 cin.sync();cin.get();
 }