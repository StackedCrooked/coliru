#include <iostream>
#include <vector>

class Pala {
    int x;
public:
    Pala();
    Pala(int);
    int arvo() const;
};

/* Funktiot */
void kasittele_vect(std::vector<Pala>, std::vector<int>);
//bool kasittele_vect(std::vector<Pala>&, const std::vector<int>&);

int main(int argc, char* argv[]) {
    std::vector<Pala> pala_vect;
    std::vector<int> int_vect;
    int_vect.push_back(1);
    int_vect.push_back(2);
    
    kasittele_vect(pala_vect, int_vect);
    
    for (auto i = pala_vect.begin(); i != pala_vect.end(); ++i) {
        std::cout << i->arvo() << std::endl;
    }
    return 0;
}
void kasittele_vect(std::vector<Pala> palat, std::vector<int> lisays) {
    for (auto i = lisays.begin(); i != lisays.end(); ++i) {
        palat.push_back(Pala(*i));
    }
}
Pala::Pala() : x(0) {
}
Pala::Pala(int arvo) : x(arvo) {
}
int Pala::arvo() const {
    return x;
}