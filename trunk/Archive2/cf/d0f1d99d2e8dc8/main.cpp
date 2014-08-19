#include <iostream>
#include <memory>
 
class Superclass {
public:
    virtual void Announce() {
        printf("I am the superclass\n");
    }
};

class Subclass : public Superclass {
public:
    void Announce() {
        printf("I am the subclass\n");
    }
};

int main() {
    Superclass osuper;
    Subclass osub;

    Superclass* p = &osub;
    *p = osuper;
    osub.Announce();

    return 0;
}