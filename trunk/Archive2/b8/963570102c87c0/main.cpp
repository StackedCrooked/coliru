#include <vector>
#include <iostream>
using namespace std;

#define MIN -100
#define MAX 100

struct Monomio {
    Monomio();
    Monomio(int coef);
    Monomio(int coef, int exp);
    Monomio(const Monomio& orig);
    ~Monomio();
    int getCoeficiente() const;
    int getExponente() const;
    void setCoeficiente(int c);
    void setExponente(int e);
    int coeficiente; 
    int exponente;
};

Monomio::Monomio() {
    coeficiente = 0;
    exponente = 0;
}

Monomio::Monomio(int coef) {
    coeficiente = coef;
    exponente = 0;
}

Monomio::Monomio(int coef, int exp) {
    coeficiente = coef;
    exponente = exp;
}

Monomio::Monomio(const Monomio& orig) {
}

Monomio::~Monomio() {
}



//Getters & Setters:
int Monomio::getCoeficiente() const {
    return coeficiente;
}

int Monomio::getExponente() const {
    return exponente;
}

void Monomio::setCoeficiente(int c) {
    this->coeficiente = c;
}

void Monomio::setExponente(int e) {
    this->exponente = e;
}

ostream& operator<<(ostream& out, const Monomio& a) {
    //TODO: WHAT IS HERE?
    return out;
}

struct Polinomio {
    Polinomio();
    Polinomio(const Polinomio& orig);
    Polinomio(int grado);
    ~Polinomio();
    void rellenarRandom();
    void setMonomio(vector<Monomio> vec);
    int getGrado() const;
    vector<Monomio> getMonomios() const;
    void rellenarRandom(int grado);
    void setGrado(int grado);
    
    vector<Monomio> monomios;
    int grado;
};

Polinomio::Polinomio() {
    setGrado(0);
    setMonomio(vector<Monomio> (0));
    srand (time(NULL));
}

Polinomio::Polinomio(const Polinomio& orig) {
    setGrado(orig.getGrado());
    setMonomio(orig.getMonomios());
    srand (time(NULL));
}

Polinomio::Polinomio(int grado) {
    setGrado(grado);
    cout << "grado:" << getGrado() << endl;
    Monomio mon;
    setMonomio(vector<Monomio> (getGrado() + 1, mon));
    srand (time(NULL));
}

Polinomio::~Polinomio() {
}

int Polinomio::getGrado() const {
    return this->grado;
}

vector<Monomio> Polinomio::getMonomios() const {
    return this->monomios;
}

void Polinomio::rellenarRandom() {
    Monomio mon;
    vector<Monomio> vec (getGrado() + 1, mon);

    for (int i = 0; i <= getGrado(); i++) {
//        int random = MIN + (rand() % (int)(MAX - MIN + 1));
        int random = 1 +  i;
        Monomio mon (random, i);
        vec[i] = mon;
    }

    cout << "VEC :";
    cout << vec[0] << endl;

    setMonomio(vec);
    auto v = monomios;

    cout << "V: ";
    cout << v[0] << endl;
}

void Polinomio::rellenarRandom(int grado) {

}

void Polinomio::setGrado(int grado) {
    this->grado = grado;
}

void Polinomio::setMonomio(vector<Monomio> vec) {
    cout << "set: " << vec[0] << endl;
    this->monomios = vec;
    cout << "postset: " << this->monomios[0] << endl;
}

inline ostream& operator<< (ostream& o, const Polinomio &a) {
    auto v = a.getMonomios();
    for (vector<Monomio>::iterator it = v.begin(); it != v.end(); ++it)
        o << *it << " + ";
    return o;
}

int main() {
    Polinomio pol (5); // Creates a Polinomial with grade 5
    pol.rellenarRandom();
    cout << "pol: " << pol << endl;
}