#include <iostream>
#include <string>

class Weapon {
    public:
       Weapon() { m_damage = -2; }
       int get_damage() { return m_damage; }
       void SetDamage(int d) { m_damage = d; }
    private:
        int m_damage;
};

class Character {
    public:
        Character() {}
        Character(std::string name) {
            MyName = name;
            MyWeapon.SetDamage(2);
        }
        virtual int GetDamage() { return MyWeapon.get_damage(); }
    protected:
        std::string MyName;
        Weapon MyWeapon;
};

class Mage : public Character {
    public:
    Mage(std::string name) { MyWeapon.SetDamage(1); }
};

class Warrior : public Character {
    public:
    Warrior(std::string name) { MyWeapon.SetDamage(10); }
};

int main()
{
    Character Me("Chemistpp");
    Mage You("User");
    Warrior Ghandi("Boss");
    
    std::cout << Me.GetDamage() << std::endl;
    std::cout << You.GetDamage() << std::endl;
    std::cout << Ghandi.GetDamage() << std::endl;
    
    return 0;
}
