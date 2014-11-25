#include <iostream>

class Moebel {
public:
    void ausgeben() {
        std::cout << "irgendwas\n";
    }
};

class Stuhl : public Moebel {
public:
    void ausgeben() {
        std::cout << "ein Stuhl\n";
    }
};

void moebelAusgeben(Moebel &m) {
    m.ausgeben();
}

int main() {
    Moebel m;
    Stuhl s;
    
    m.ausgeben();
    s.ausgeben();
    
    moebelAusgeben(m);
    moebelAusgeben(s);
}
