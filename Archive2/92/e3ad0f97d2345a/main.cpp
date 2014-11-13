/**
 * Assignment: hw05
 * Name:       Max Marrone
 * Email:      mmarrone@nyu.edu
 * NYU ID:     N12033468
 * NYU NetID:  mpm507
 * 
 * Description:
 *   An exercise in inheritance.
 * Notes:
 *   Here's the inheritance tree:
 *   Person
 *       BattlePerson
 *           PersonWithStrengthToFight
 *           Lord
 *       Protector
 *           Wizard
 *           Warrior
 *               Swordsman
 *               Archer
 **/


#include <vector>
#include <string>
#include <iostream>

using namespace std;

// Person is the root class of the hierarchy.  Everyone has a name and a
// calculable strength that can be lost.
class Person
{
    string name;
	public:
	Person(const string& name) : name(name) { }
	string getName() const { return name; }
	virtual double getStrength() const = 0;
	virtual bool isDead() const { return getStrength() == 0; }
	protected:
	virtual void loseStrength(const double amount) = 0;
};

// A BattlePerson is able to do battle with another BattlePerson.
class BattlePerson: public Person
{
	bool dead;
	
	public:
	
	BattlePerson(const string& name)
		: Person(name), dead(false) { }
	
	virtual void battle(BattlePerson& opponent, ostream& output = cout)
	{
		// Cache each side's strength in case it's expensive to calculate.
		const double strength = getStrength();
		const double opponentStrength = opponent.getStrength();
		
		output << getName() << " battles " << opponent.getName() << "\n";	
		
		if (dead && opponent.dead)
			output << "Oh, NO!  They're both dead!  Yuck!";
		else if (dead)
			output << "He's dead, " << opponent.getName();
		else if (dead)
			output << "He's dead, " << getName();
		
		else // Both sides have strength to fight.
		{
			intimidateOpponent(output);
			opponent.intimidateOpponent(output);
			
			if (strength > opponentStrength)
				output << getName() << " defeats " << opponent.getName();
			else if (strength < opponentStrength)
				output << opponent.getName() << " defeats " << getName();
			else output << "Mutual Annihalation: "
			            << getName() << " and " << opponent.getName()
			            << " die at each other's hands";
			
			// Update each side's strength.
			const double lostStrength = strength < opponentStrength ?
			                            strength : opponentStrength;
			loseStrength(lostStrength);
			opponent.loseStrength(lostStrength);
			
			if (!getStrength()) dead = true;
			if (!opponent.getStrength()) opponent.dead = true;
		}
		
		output << "\n";
	}
	
	bool isDead() const { return dead; }
	
	protected:
	
	virtual void intimidateOpponent(ostream& output) const { };
	virtual void loseStrength(double amount) = 0;
};


// A PersonWithStrengthToFight fights for him/herself.
class PersonWithStrengthToFight: public BattlePerson
{
	double strength;
	public:
	PersonWithStrengthToFight(const string& name, const double strength)
		: BattlePerson(name), strength(strength) { }
	virtual double getStrength() const override { return strength; }
	protected:
	virtual void loseStrength(const double amount) override
	{
		strength -= amount;
		if (strength < 0) strength = 0;
	}
};

// A Lord only gets strength from hired Protectors, but can still do battle.
class Protector;
class Lord: public BattlePerson
{
	std::vector<Protector*> protectors;
	public:
	using BattlePerson::BattlePerson;
	void hires(Protector& protector);
	void fires(Protector& protector);
	virtual double getStrength() const override;
	virtual void intimidateOpponent(ostream& output = cout) const override;
	protected:
	virtual void loseStrength(const double amount) override;
};

// Protectors can be hired by Lords to provide strength, but they can't battle
// on their own.  Derived classes need to override protect() to output an
// intimidating message.
class Protector: public Person
{
	// Previously, we had a public setLord() function to set the internal lord
	// pointer.  That's a bad thing to do because it lets users of this class
	// violate its invariants, like so:
	// 
	// lordA.hire(protector);
	// protector.setLord(lordB); // Now protector will output the wrong lord name.
	// protector.setLord(nullptr);
	// lordC.hire(protector); // Hired by both A and C.  All hell breaks loose!
	// 
	// Clearly, then, it doesn't make sense to have a public Protector::setLord().
	// What we do instead is make Lord a friend class here, so Lord can directly
	// set Protector's internal pointer.  This way, the ONLY way for calling
	// code to get at the pointer is to go through Lord::hire()/Lord::fire().
	friend class Lord;
	// Before you tell me that this violates encapsulation or something, please
	// consider what encapsulation means for a pair of classes as tightly
	// coupled as Lord and Protector.  It doesn't mean keeping their internal
	// details separate from each other.  It means keeping their COLLECTIVE
	// API sanitized, safe and detail-free for CALLING code.

	Lord* lord;
	double strength;
	public:
	Protector(const string& name, const double strength)
		: Person(name), lord(nullptr), strength(strength) { }
	virtual void battleCry(ostream& output) const = 0;
	virtual double getStrength() const override { return strength; }
	const Lord* getLord() const { return lord; }
	Lord* getLord() { return lord; }
	
	protected:
	
	virtual void loseStrength(const double amount) override
	{
		strength -= amount;
		if (strength < 0) strength = 0;
	}
};

void Lord::hires(Protector& protector)
{
	if (!isDead() && !protector.isDead() && !protector.getLord())
	{
		protectors.push_back(&protector);
		protector.lord = this; // See the comment in Protector for why we don't
		                       // use a setLord() method.
	}
}

void Lord::fires(Protector& protectorToFire)
{
	for (Protector*& protector: protectors)
	{
		if (protector == &protectorToFire)
		{
			// Reset the Protector's pointer so it can be hired again.
			protector->lord = nullptr;
			
			// Write over the Protector's entry in the vector.
			protector = protectors.back();
			protectors.pop_back();
			
			break;
		}
	}
}

void Lord::intimidateOpponent(ostream& output) const
{
	for (const Protector* const protector: protectors)
		protector->battleCry(output);
}

double Lord::getStrength() const
{
	double totalStrength = 0;
	for (Protector* const protector: protectors)
		totalStrength += protector->getStrength();
	return totalStrength;
}

void Lord::loseStrength(const double amount)
{
	const double percentageLost = amount/getStrength();
	for (Protector* const protector: protectors)
		protector->loseStrength(percentageLost*protector->getStrength());
}

class Wizard: public Protector
{
	using Protector::Protector;
	public:
	virtual void battleCry(ostream& output) const override
	{
		if (!isDead()) output << "POOF!\n";
	}
};

class Warrior: public Protector
{
	using Protector::Protector;
	public:
	virtual void battleCry(ostream& output) const override = 0;
};

void Warrior::battleCry(ostream& output) const
{
	output << getName() << " says: ";
	if (getLord() && !isDead()) output << "Take that in the name of my lord, "
		                               << getLord()->getName() << "!\n";
	else output << "I don't have a lord!\n";	            
}

class Archer: public Warrior
{
	using Warrior::Warrior;
	public:
	virtual void battleCry(ostream& output) const override
	{
		if (getLord() && !isDead()) output << "TWANG!  ";
		Warrior::battleCry(output);
	}
};

class Swordsman: public Warrior
{
	using Warrior::Warrior;
	public:
	virtual void battleCry(ostream& output) const override
	{
		if (getLord() && !isDead()) output << "CLANG!  ";
		Warrior::battleCry(output);
	}
};

int main()
{
	Lord sam("Sam");
    Archer samantha("Samantha", 200);
    sam.hires(samantha);
    Lord joe("Joe");
    PersonWithStrengthToFight randy("Randolf the Elder", 250);
    joe.battle(randy);
    joe.battle(sam);
    Lord janet("Janet");
    Swordsman hardy("TuckTuckTheHardy", 100);
    Swordsman stout("TuckTuckTheStout", 80);
    janet.hires(hardy);
    janet.hires(stout);
    PersonWithStrengthToFight barclay("Barclay the Bold", 300);
    janet.battle(barclay);
    janet.hires(samantha);
    Archer pethora("Pethora", 50);
    Archer thora("Thorapleth", 60);
    Wizard merlin("Merlin", 150);
    janet.hires(pethora);
    janet.hires(thora);
    sam.hires(merlin);
    janet.battle(barclay);
    sam.battle(barclay);
    joe.battle(barclay);
    
    // Make sure protectors can only be hired once.
    Lord a("a");
    Lord b("b");
    Swordsman s("s", 100);
    a.hires(s);
    b.hires(s);
    std::cout << "Lord who hired first: " << a.getStrength() << ".  "
              << "Lord who hired second: " << b.getStrength() << "."
              << std::endl;
}