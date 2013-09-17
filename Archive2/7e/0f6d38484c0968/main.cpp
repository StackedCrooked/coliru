#include <iostream>


struct ejaculator {
    ejaculator operator~() {
        return {};
    }
};

struct annoyance {    
};

struct slut {
    annoyance operator<(ejaculator) {
        return {};
    }
};


int main()
{
    ejaculator penis;
    slut vagina;
    
    auto baby = vagina <~~~~~~~~~~~ penis;
}
