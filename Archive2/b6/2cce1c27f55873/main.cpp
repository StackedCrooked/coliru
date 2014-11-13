/**
 * Assignment: hw02
 * Name:       Max Marrone
 * Email:      mmarrone@nyu.edu
 * NYU ID:     N12033468
 * NYU NetID:  mpm507
 * 
 * Description:
 *   This program reads a file (warriors.txt) and parses its contents as a set
 *   of commands: "Warrior", "Battle" and "Status".  Depending on the command,
 *   the program then creates a new Warrior object with a given name, weapon and
 *   weapon strength, or it simulates a battle between two warriors, or it 
 *   prints all warriors' status, respectively.
 *
 * Notes:
 *   - Compile with --std=c++11.
 *   - Minor liberties have been taken with the output to improve readability.
 * 
 * Known issues:
 *   - The syntax of the input file is assumed valid.
 *   - The semantics of the input file (not battling a warrior that hasn't been
 *     created yet, etc.) are assumed valid.
 **/

#include <cassert> // For the assert() macro, which is used a couple of times.
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

// POD type for a warrior's weapon.  There's no point in hiding any data here;
// a weapon, on its own, is just an aggregate of a name and strength.
struct Weapon
{
    std::string name;
	unsigned int strength;
};

class Warrior
{
	Weapon weapon;
	
	public:
	
	// The assignment doesn't specify any restrictions on warrior names.
	// Since a name can be *any* string, there's no point in wrapping that
	// string in cumbersome accessors and modifiers.
	std::string name;
	
	Warrior(const std::string& name, const std::string& weaponName, unsigned int strength);
	
	unsigned int getStrength() const;
	void setStrength(unsigned int strength);
	
	// Return a const ref to save having to copy the weapon's name.
	const std::string& getWeaponName() const;
};

// Prints the given warrior's strength and name to output.
// This should really be an overloaded operator<<.
void printWarrior(const Warrior& warrior, std::ostream& output = std::cout);

// Finds the first warrior in haystack with the given name.  If no such warrior
// exists, the last warrior is returned.  Assumes haystack.size() >= 1.
// Note: haystack cannot be const because we want to return a Warrior&, not a
// const Warrior&.  This is only possible if haystack allows its elements to be
// mutated.
Warrior& findWarrior(std::vector<Warrior>& haystack, const std::string& needle);

// Prints the size and contents of the given Warrior vector to the given
// output stream.
void printStatus(const std::vector<Warrior>& warriors,
                 std::ostream& output = std::cout);

// Runs a battle between the two given warriors, updating their respective
// strengths and outputting the result to the given output stream.
void battle(Warrior& warrior1, Warrior& warrior2,
            std::ostream& output = std::cout);

// Helper function for battle() to handle the case where one warrior fairly
// defeats the other.
// Important assumption: a.getStrength() > b.getStrength().
void aDefeatB(Warrior& warriorA, Warrior& warriorB, std::ostream& output = std::cout);

int main()
{
	std::vector<Warrior> warriors;
	std::ifstream input("warriors.txt");
	
	if (!input)
	{
		std::cerr << "Error: Couldn't open the input file." << std::endl;
		return 1;
	}
	
	else
	{
		std::string command;
		while (input >> command)
		{
			if (command == "Status") printStatus(warriors);
			
			else if (command == "Warrior") // Add a new warrior.
			{
				std::string warriorName, weaponName;
				unsigned int strength;
				input >> warriorName >> weaponName >> strength;
				
				// This didn't seem complex enough to warrant its own helper function.
				Warrior warrior(warriorName, weaponName, strength);
				warriors.push_back(warrior);
			}
			
			else if (command == "Battle")
			{
				std::string name1, name2;
				input >> name1 >> name2;
				battle(findWarrior(warriors, name1),
				       findWarrior(warriors, name2));
			}
		}
		
		return 0;
	}
}

Warrior::Warrior(const std::string& name,
                 const std::string& weaponName,
                 const unsigned int strength):
	name(name), weapon{weaponName, strength}
{
	assert(strength >= 0); // Strengths can't be negative.
}

unsigned int Warrior::getStrength() const
{
	return weapon.strength;
}

void Warrior::setStrength(const unsigned int strength)
{
	assert(strength >= 0); // Strengths can't be negative.
	weapon.strength = strength;
}

const std::string& Warrior::getWeaponName() const
{
	return weapon.name;
}

void printWarrior(const Warrior& warrior, std::ostream& output)
{
	output << warrior.name
	       << " (weapon \"" << warrior.getWeaponName() << "\","
	       << " strength " << warrior.getStrength() << ")";
}

Warrior& findWarrior(std::vector<Warrior>& haystack, const std::string& needle)
{
	for (auto& warrior: haystack)
		if (warrior.name == needle) return warrior;
	return haystack.back(); // Fall back to returning the last element.
}

void printStatus(const std::vector<Warrior>& warriors, std::ostream& output)
{
	output << "There are " << warriors.size() << " warriors: " << std::endl;
	for (const auto& warrior: warriors)
	{
		output << "\t"; // For pretty formatting.
		printWarrior(warrior, output);
		output << std::endl;
	}
}

void battle(Warrior& warrior1, Warrior& warrior2, std::ostream& output)
{
	output << warrior1.name << " battles " << warrior2.name << ".\n\t";
	
	// If both warriors are already dead, there's no battle to be had.
	if (warrior1.getStrength() == 0 && warrior2.getStrength() == 0)
		output << "Oh, NO!  They're both dead!  Yuck!" << std::endl;
	
	// A tie.
	else if (warrior1.getStrength() == warrior2.getStrength())
	{
		warrior1.setStrength(0);
		warrior2.setStrength(0);
		output << "Mutual annihilation: "
		       << warrior1.name << " and " << warrior2.name
		       << " die at each other's hands."
		       << std::endl;
	}
	
	// One warrior is already dead.  The other one "wins."
	else if (warrior1.getStrength() == 0)
		output << "He's dead, " << warrior2.name << "." << std::endl;
	else if (warrior2.getStrength() == 0)
		output << "He's dead, " << warrior1.name << "." << std::endl;
	
	// One warrior fairly defeats the other.
	else if (warrior1.getStrength() > warrior2.getStrength())
		aDefeatB(warrior1, warrior2, output);
	else if (warrior2.getStrength() > warrior1.getStrength())
		aDefeatB(warrior2, warrior1, output);
	
	// Shouldn't be possible; every possibility SHOULD be accounted for above.
	else assert(false);
}

void aDefeatB(Warrior& warriorA, Warrior& warriorB, std::ostream& output)
{
	assert(warriorA.getStrength() > warriorB.getStrength());
	warriorA.setStrength(warriorA.getStrength() - warriorB.getStrength());
	warriorB.setStrength(0);
	output << warriorA.name << " defeats " << warriorB.name << "." << std::endl;
}