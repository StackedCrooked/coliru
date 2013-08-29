#include <iostream>
using std::cout;
using std::endl;

    //Characters.h
    class Characters
    {
    private:
        int level;
        int hp;
        int attack;
        int defense;
    protected:
        Characters(); // zero everything by default
        Characters(int, int, int, int); // populate explicitly
        ~Characters();
    public:
        int getAttack() const { return attack; }
        int getDefense() const { return defense; }
        int getHp() const { return hp; }
        int getlevel() const { return level; }

        void setAttack(int);
        void setDefense(int);
        void setStrength(int);
        void setHp(int);
        void setlevel(int);
        void damageTaken(int);
    };



    //Monsters.h
    class Monsters:
        public Characters //Hero
    {
    private:
        int Monsterlevel;
        int MonsterHp;
        int MonsterStrength;
        int MonsterAttack;
        int MonsterDefense;
    public:
        Monsters(int, int, int, int); //explicit
        ~Monsters();
    };

    //Monsters.cpp
    Monsters::~Monsters()
    {
        cout << "\nMonster Destroyed";
    }

    //Hero.h
    class Hero:
        public Characters
    {
    private:
        int Herolevel;
        int HeroHp;
        int HeroStrength;
        int HeroAttack;
        int HeroDefense;

    public:
        //Hero();
        Hero(int, int, int, int);
        ~Hero();

    };

    //Characters.cpp
    Characters::Characters() : level(0), hp(0), attack(0), defense(0) {}
    //
    //Characters::Characters(int seed)
    //{
    //    // NB. your code still doesn't initialize hp, strength etc.
    //    // it also logs level before initializing it, so that will be garbage
    //}

    Characters::Characters(int hit, int lvl, int att, int def)
     : level(lvl), hp(hit), attack(att), defense(def){}

    Hero::Hero(int newHp, int newLevel, int newAttack, int newDef)
        : Characters(newHp, newLevel, newAttack, newDef)
    {
        cout << "Hero created using Overloaded function!\n";
        HeroHp = newHp;
        cout << "Hp is: "<< HeroHp << endl;
        Herolevel = newLevel;
        cout << "level is: " << Herolevel << endl;
        HeroAttack = newAttack;
        cout << "Attack is: " << HeroAttack << endl;
        HeroDefense = newDef;
        cout << "Defense is: " << HeroDefense << endl;
        // logging goes here
        // note that you don't need HeroLevel etc. at all any more, just use level
    }

    Monsters::Monsters(int newHp, int newLevel, int newAttack, int newDef)
        : MonsterHp(newHp), Monsterlevel(newLevel), MonsterAttack(newAttack)
    , MonsterDefense(newDef)//initialize list
    {
        cout << "Monster created using Overloaded function!\n";
        MonsterHp = newHp;
        cout << "Hp is: "<< MonsterHp << endl;
        Monsterlevel = newLevel;
        cout << "level is: " << Monsterlevel << endl;
        MonsterAttack = newAttack;
        cout << "Attack is: " << MonsterAttack << endl;
        MonsterDefense = newDef;
        cout << "Defense is: " << MonsterDefense << endl;
    }


    Characters::~Characters()
    {
        cout << "Character has been destroyed!\n";
    }

    void Characters::setAttack(int att)
        {
            attack = att;
        }

    void Characters::setDefense(int def)
        {
            defense = def;
        }

    void Characters::setHp(int health)
        {
            hp = health;
        }

    void Characters::damageTaken(int damage)
        {
            hp -= damage;
        }

    void Characters::setlevel(int lvl)
        {
            level = lvl;
        }

    //Hero.cpp
    Hero::~Hero()
    {
        cout << "Hero destroyed!\n";
    }
    
    
    
    //main.cpp
    int main()
    {
        Hero Me(100,20,30,40);//Created using overloaded constructor
        Monsters m(100,16,18,20);//creates a monster object and uses overloaded constructor to initialize
        std::cout << "\ntest1\n";
        Me.getHp();//expecting 100
        Me.getAttack();//expecting w.e is in parameters

        m.getHp();//expecting 100
        m.getAttack();//same as hero


  
        return 0;
    }