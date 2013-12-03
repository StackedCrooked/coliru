#include <boost/variant.hpp>
#include <iostream>
#include <string>
#include <vector>

using std::string;

struct STUDENCI
{
    int indeks;
    string imie;
    string nazwisko;
};

struct PRZEDMIOTY
{
    int id;
    string nazwa;   
    int semestr;    
};

struct SALE
{
    string nazwa;
    int rozmiar;    
    bool projektor;
    double powierzchnia;
};

typedef std::vector<boost::variant<STUDENCI, PRZEDMIOTY, SALE> > Vector;

int main()
{
    Vector v;
    v.push_back(STUDENCI { 1, "imie", "nazwisko" });
    v.push_back(PRZEDMIOTY { 1, "eng101", 3 });
    v.push_back(SALE { "auditorium", 42, true, 250 });
}
