#ifndef WEIHNACHTSMANN_H
#define WEIHNACHTSMANN_H

#include <string>

typedef int Euro;
using Euro = int;

struct GeschenkElement;

class Weihnachtsmann {
public: 
    Weihnachtsmann();
    void neuesGeschenk(std::string beschreibung, Euro preis);
    void weihnachtsabend();
private:
    GeschenkElement * geschenke;
};

class Geschenk {
public: 
    Geschenk();
    void geschenkInhalt();
private: 
    std::string beschreibung;
    Euro preis;
};

#endif//WEIHNACHTSMANN_H