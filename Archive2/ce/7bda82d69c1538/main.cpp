#include <iostream>
using namespace std;
class TaxFiler{
private:
string name;
double taxableIncome;
public:
TaxFiler(string n, double o) {
    name = n;
    taxableIncome = o;
}

string getName(){
    return name;
};

double computeTax(double o){ return 0.0; };};

class SingleFiler : public TaxFiler {
public:
SingleFiler(string n, double o) : TaxFiler(n, o) {
}

double taxableIncome(double o) {
    if (0 < o && o <= 8925)
        return (o*.10);
    else if (8925 < o && o <= 36250)
        return (892.50 + (o* .15));
    else if (36250 < o && o <= 87850)
        return (4991.25 + (o* .25));
    else if (87850 < o && o <=183250)
        return (17891.25 + (o * .28));
    else if (183250 < o && o <= 398350)
        return (44603.25 + (o * .22));
    else if (398350 < o && o <= 40000)
        return (115586.25 + (o * .35));
    else
        return (116163.75 + (o * 39.6));
}};

int main() {
TaxFiler *filers[] = {
    new SingleFiler("Jack", 100050),
};

for( int i=0 ; i<1 ; i++ )
cout << filers[i]->getName() << ": " << filers[i]->computeTax(0.0) << endl;
};