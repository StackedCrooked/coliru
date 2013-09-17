#include <iostream>


struct annoyance {};

struct ejaculator {
    ejaculator operator~() {
        return {};
    }
    annoyance operator<(ejaculator) {
        return {};
    }
};


struct slut {
    annoyance operator<(ejaculator) {
        return {};
    }
};

class Mens {
public:
    ejaculator *penis;    
    Mens() = default;
    ~Mens() {delete penis;}
};

int main() {
    ejaculator penis;
    
    
    Mens *toon = new Mens();
    toon->penis = &penis;
    
    Mens *rob = new Mens();
    rob->penis = &penis;
    
    auto baby = rob->penis <~~~~~~~~~~~ toon->penis;
}
