#include <iostream>
#include <memory>
#include <utility>
#include <list>

struct MonsterHitDice {
    constexpr MonsterHitDice( double level, int adjustment, int specialAbilitiesBonus )
        : level(level), adjustment(adjustment), specialAbilitiesBonus(specialAbilitiesBonus) {}
    const double level;
	const int adjustment;
	const int specialAbilitiesBonus;
};

struct Monster {
    virtual ~Monster() = default ;

	virtual MonsterHitDice HitDice() const = 0;
	virtual int ArmorClass() const = 0;
    virtual int NumberOfAttacks() const = 0;
	// etc.
};

template <typename DERIVED, int AC, int NATTACKS>
struct MonsterType: virtual Monster {
    static int armorClass, numberOfAttacks;
    virtual int ArmorClass() const override {return armorClass;}
    virtual int NumberOfAttacks() const override {return numberOfAttacks ;}
    // etc.
};

template <typename DERIVED, int AC, int NATTACKS>
int MonsterType<DERIVED, AC, NATTACKS>::armorClass = AC;

template <typename DERIVED, int AC, int NATTACKS>
int MonsterType<DERIVED, AC, NATTACKS>::numberOfAttacks = NATTACKS;
//// etc.

template < typename DERIVED, int ADJ, int BONUS, int LEVEL_NUM, int LEVEL_DEN = 1  >
struct HitDeviceType : virtual Monster {
	static MonsterHitDice hitDice;
	virtual MonsterHitDice HitDice() const override {return hitDice;}
};

template < typename DERIVED, int ADJ, int BONUS, int LEVEL_NUM, int LEVEL_DEN >
MonsterHitDice HitDeviceType< DERIVED, ADJ, BONUS, LEVEL_NUM, LEVEL_DEN >::hitDice =
{ double(LEVEL_NUM)/LEVEL_DEN, ADJ, BONUS } ;

struct Goblin: MonsterType<Goblin, 6, 1>, HitDeviceType<Goblin,-1,0,1>  {};
struct Dragon: MonsterType<Dragon, -2, 3>, HitDeviceType<Dragon,20,0,1>  {};
struct Troll: MonsterType<Troll, 2, 3>, HitDeviceType<Troll,0,2,8> {};

int main() {
   	std::list<Monster*> monsters = {new Goblin(), new Dragon(), new Troll()};
	for (const auto& x: monsters)
		std::cout << x->HitDice().level << ", " << x->HitDice().adjustment <<
 ", " << x->ArmorClass() << ", " << x->NumberOfAttacks() << std::endl;	std::cout << Goblin::hitDice.level << ", " << Goblin::hitDice.adjustment
 << ", " << Goblin::armorClass << ", " << Goblin::numberOfAttacks << std::endl;
}
