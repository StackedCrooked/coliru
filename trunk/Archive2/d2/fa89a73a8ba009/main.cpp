#include <iostream>

class Weapon {
public:
    void weaponSelect(WEAPONTYPE choice);
protected:
    enum WEAPONTYPE {
        LASER = 0,
        ROCKET = 1
    };
};

void Weapon::weaponSelect(Weapon::WEAPONTYPE enumChoice) {}

int main() {
    return 0;
}