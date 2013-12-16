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
    friend std::ostream& operator << (std::ostream& os, STUDENCI const& v) {
        return os << "STUDENCI { " << v.indeks << ", " << v.imie << ", " << v.nazwisko << " }";
    }
};

struct PRZEDMIOTY
{
    int id;
    string nazwa;   
    int semestr;    
    friend std::ostream& operator << (std::ostream& os, PRZEDMIOTY const& v) {
        return os << "PRZEDMIOTY { " << v.id << ", " << v.nazwa << ", " << v.semestr << " }";
    }
};

struct SALE
{
    string nazwa;
    int rozmiar;    
    bool projektor;
    double powierzchnia;
    friend std::ostream& operator << (std::ostream& os, SALE const& v) {
        return os << "SALE { " << v.nazwa << ", " << v.rozmiar << ", " 
                  << std::boolalpha << v.projektor << ", " << v.powierzchnia << " }";
    }
};

typedef std::vector<boost::variant<STUDENCI, PRZEDMIOTY, SALE> > Vector;

int main()
{
    Vector v;
    v.push_back(STUDENCI { 1, "imie", "nazwisko" });
    v.push_back(PRZEDMIOTY { 1, "eng101", 3 });
    v.push_back(SALE { "auditorium", 42, true, 250 });

    for (auto& element: v)
        std::cout << element << "\n";
}
