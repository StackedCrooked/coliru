#include <iostream>

class Klasse {
public:
    int i;
    
    void ausgeben() {
        std::cout << "ausgeben: " << i << '\n';
    }
};

void klasseAusgeben(const Klasse &k) {
    std::cout << "klasseAusgeben: " << k.i << '\n';
}

int main() {
    Klasse k1{1};
    Klasse k2{2};
    k1.ausgeben();
    klasseAusgeben(k1);
    k2.ausgeben();
    klasseAusgeben(k2);
}
