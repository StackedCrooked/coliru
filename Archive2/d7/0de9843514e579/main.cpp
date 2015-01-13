#include <iostream>
#include <memory>
#include <unordered_map>
#include <string>

struct LivingBeing {
    std::string name;
	LivingBeing() = default;
	LivingBeing (const std::string& n) : name(n) {}
    virtual ~LivingBeing() = default;
    virtual void chooseAction() = 0;
};

struct Wizard : LivingBeing {
	using LivingBeing::LivingBeing;
	virtual void chooseAction() override {}
};

struct Monster : virtual LivingBeing {
	using LivingBeing::LivingBeing;
	virtual void chooseAction() override {std::cout << "Monster::chooseAction() called.\n";}
};

struct Wolf : virtual Monster {
	using Monster::Monster;
	virtual void chooseAction() override {std::cout << "Wolf::chooseAction() called.\n";}
};

struct SummonedMonsterStrategy {
	struct Exemplar {};
	LivingBeing* summonedMonster;
	static std::unordered_map<std::string, SummonedMonsterStrategy*> prototypesMap;

	SummonedMonsterStrategy (LivingBeing* monster) : summonedMonster(monster) {}
	SummonedMonsterStrategy (Exemplar, const std::string& name) {insertInPrototypesMap (name, this);}
	virtual ~SummonedMonsterStrategy() = default;
	static const std::unordered_map<std::string, SummonedMonsterStrategy*>& getPrototypesMap() {return prototypesMap;}
	virtual void execute() = 0;
	static void insertInPrototypesMap (const std::string& tag, SummonedMonsterStrategy* strategy) {
		prototypesMap.emplace (tag, strategy);
		std::cout << "{" << tag << ", " << strategy << "} inserted in SummonedMonsterStrategy::prototypesMap." << std::endl;
	}
};
std::unordered_map<std::string, SummonedMonsterStrategy*> SummonedMonsterStrategy::prototypesMap;

struct AttackEnemiesOfSummoner : SummonedMonsterStrategy {
	static const AttackEnemiesOfSummoner prototype;
	using SummonedMonsterStrategy::SummonedMonsterStrategy;
	AttackEnemiesOfSummoner (Exemplar e) : SummonedMonsterStrategy (e, "Attack Enemies Of Summoner") {}
	virtual void execute() override;
};
const AttackEnemiesOfSummoner AttackEnemiesOfSummoner::prototype (Exemplar{});

struct SummonedMonster : virtual Monster {
	LivingBeing* summoner;
	SummonedMonster (LivingBeing* s) : summoner(s) {}
	////////////////////////////////////////////////////////////////////////
	virtual void do_choose_action() = 0 ; // **** added ****
	////////////////////////////////////////////////////////////////////////
};

template <typename T>
struct Summoned : SummonedMonster, T {  // Adapter Pattern
	std::shared_ptr<SummonedMonsterStrategy> summonedMonsterStrategy;
	Summoned (LivingBeing* summoner, const std::string& name) : LivingBeing(name), SummonedMonster(summoner) {
		summonedMonsterStrategy = std::make_shared<AttackEnemiesOfSummoner>(this);
	}
	virtual void chooseAction() override {summonedMonsterStrategy->execute();}  // This I want to use now.
	////////////////////////////////////////////////////////////////////////
	virtual void do_choose_action() override {T::chooseAction();} // **** added ****
	////////////////////////////////////////////////////////////////////////
};

void AttackEnemiesOfSummoner::execute() {
    ////////////////////////////////////////////////////////////////////////
	dynamic_cast<SummonedMonster*>(summonedMonster)->do_choose_action() ; // **** modified ****
    ////////////////////////////////////////////////////////////////////////
}

int main() {
	Wizard wizard ("Wizard");
	Summoned<Wolf> summonedWolf (&wizard, "Summoned Wolf");
	summonedWolf.chooseAction();  // Monster::chooseAction() called.
}
//  Want to have "Wolf::chooseAction() called." to be the output though.
