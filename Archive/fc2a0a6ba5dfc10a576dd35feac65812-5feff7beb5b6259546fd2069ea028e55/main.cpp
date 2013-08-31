class Warrior {
    public:
        int health;
        Warrior() : health(100) {}
        void attack(Warrior &target) {
            target.health -= 10;
        }
};

#include <iostream>

int main(){
Warrior w1;
Warrior w2;
w1.attack(w2);
std::cout << w2.health;
}