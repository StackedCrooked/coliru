#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

class Pupu
{
    public:
    std::string sukupuoli;
    std::string vari;
    int ika;
string getVari(){return vari;
}
Pupu(){
    sukupuoli = Functionsukupuoli(50);
    vari = Functionvari();
    ika = Functionika(0);


    }

std::string Functionsukupuoli (int a)
 {
       std::string tulos;
       int r = rand() % 101;
    if (a > r){
        tulos = "Mies"; 
    }
    else {
        tulos = "Nainen";
    }
    return tulos;
}

std::string Functionvari()
{
std::string vari;
int z = rand() % 5;
if (z == 1){
    vari = "Ruskea";
}
else if (z == 2){
    vari == "Musta";
}
else if (z == 3){
    vari = "Valkoinen";
}
else{
    vari =  "Violetti";
}
return vari;
}

int Functionika (int c)
{
    int x = rand() % 11;
    x = c;
    return c;

}


};
int main(){
    Pupu  testi = Pupu();
    cout << testi.getVari();
}