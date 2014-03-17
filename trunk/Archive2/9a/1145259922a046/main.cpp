#include <iostream>

class Player {
    private:
		std::string name;
		int hitPoints;
	public:

		Player() = default;
		Player (const std::string& newName, int hp): name (newName), hitPoints (hp) {}
		virtual ~Player() = default;
		virtual std::string Name() const {return name;}
		virtual int HitPoints() const {return hitPoints;}
		virtual void action() = 0;
		virtual void losesHitPoints (int num) {hitPoints -= num;  display();  if (hitPoints <= 0) dies();}
		void display() const {std::cout << name << "'s hit points = " << hitPoints << ".\n";}
	private:
		void dies() {std::cout << Name() << " dies!" << std::endl;  delete this;}
};

struct Fighter: public Player {
	Fighter() = default;
	Fighter (const std::string& name, int hp): Player (name, hp) {}
	virtual void action() override {std::cout << Name() << "'s action is normal.\n";}
};

struct MagicUser: public Player {
	MagicUser() = default;
	MagicUser (const std::string& name, int hp): Player (name, hp) {}
	virtual void action() override {std::cout << Name() << "'s action is normal.\n";}
};

struct PlayerDecorator: public Player {
	virtual void action() = 0;

	Player* impl ; // owning pointer ( use std::unique_ptr )
	explicit PlayerDecorator( Player* p ) : impl(p) {}
    ~PlayerDecorator() { delete impl ; } // *** added ***

	virtual std::string Name() const override {return impl->Name();}
	virtual int HitPoints() const override {return impl->HitPoints();}
	virtual void losesHitPoints (int num) override {impl->losesHitPoints (num);}
};

struct PlayerUnderHaste: public PlayerDecorator  {

    using PlayerDecorator::PlayerDecorator ;

	virtual void action() override
	{std::cout << Name() << " under Haste Spell.  Two attacks per round!\n";}
};

struct PlayerInvisible: public PlayerDecorator {

    using PlayerDecorator::PlayerDecorator ;

	virtual void action() override
	{std::cout << Name () << " under Invisibility Spell.  Cannot be hit!\n";}
};

int main() {
	Player* fighter = new Fighter( "Rex the Fighter", 8);
	Player* magicUser = new MagicUser("Merlin the Magic User", 4);
	fighter->display();  magicUser->display();
	fighter->action();  magicUser->action();

	std::cout << "Haste spell cast on Fighter and Magic User!" << std::endl;
	fighter =  new PlayerUnderHaste(fighter) ;
	magicUser = new PlayerUnderHaste(magicUser) ;
	fighter->action();  magicUser->action();
	std::cout << fighter->Name() << " hit by monster!  Loses 6 hit points!" << std::endl;
	fighter->losesHitPoints (6);

	std::cout << "Invisibility spell cast on Fighter and Magic User!" << std::endl;
	fighter = new PlayerInvisible(fighter);
	magicUser = new PlayerInvisible(magicUser);
	fighter->action();  magicUser->action();

	std::cout << "Though invisible, " << magicUser->Name() << " is caught in a fireball blast!  10 hit points lost!" << std::endl;
	magicUser->losesHitPoints (10);  // magicUser deleted automatically, but any leaking??? 
}
