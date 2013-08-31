class Warrior {
    public:
        int health;
        Warrior() : health(100) {}
        void attack(Warrior &target) {
            target.health -= 10;
        }
};

int main(){
Warrior w1;
Warrior w2;
w1.attack(w2);
}