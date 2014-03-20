#ifndef GESCHENK_H
#define GESCHENK_H

#include <string>

//typedef int Euro;
using Euro = int;

class Geschenk {
public: 
    Geschenk();
    void geschenkInhalt();
private: 
    std::string beschreibung;
    Euro preis;
};

#endif//GESCHENK

#ifndef WEIHNACHTSMANN_H
#define WEIHNACHTSMANN_H

//#include "geschenk.h"

struct GeschenkElement {
    GeschenkElement * next;
    Geschenk value;
};

class Weihnachtsmann {
public: 
    Weihnachtsmann();
    void neuesGeschenk(std::string beschreibung, Euro preis);
    void weihnachtsabend();
private:
    GeschenkElement * geschenke;
};

#endif//WEIHNACHTSMANN_H

//#include "weihnachtsmann.h"

int main() {
    Weihnachtsmann weihnachtsmann;
    weihnachtsmann.neuesGeschenk("foo", 5);
    weihnachtsmann.neuesGeschenk("bar", 10);
    weihnachtsmann.neuesGeschenk("baz", 15);
    weihnachtsmann.weihnachtsabend();
}