#include <unistd.h>
#include <iostream>
#include <fstream>
#include <cctype>
#include <vector>
#include <queue>
#include <stack>
#include <cstdlib>
#include <ctime>

class Dice
{
    public:
    Dice();
	Dice( int numSides);
	virtual int rollDice() const;
	protected:
	int numSides;
};

Dice::Dice()
{
    numSides = 6;
	srand(time(NULL)); // Seeds random number generator
}

Dice::Dice(int numSides)
{
	this->numSides = numSides;
	srand(time(NULL)); // Seeds random number generator
}

int Dice::rollDice() const
{
	return (rand() % numSides) + 1;
}


class Character
{

    public:

		std::string className;

		virtual void attack(Character* enemy);

		void fightToTheDeath(Character* enemy);

		virtual int returnAttack();

		virtual int returnDefense(); 

		virtual void recover();

		int attackPoints[2];

		int defensePoints[2];

		int armor;

		int strength;

		bool isAlive;
		

	private:

	protected:




};

/*********************************************************************
** Function: void Character::fightToTheDeath(Character* enemy)
** Description: Fights the two characters until one runs out of strenght
** Parameters: Character* enemy. pointer to enemy character to right
** Pre-Conditions: Enemy character is instantiated.
** Post-Conditions: Fight is fought. Results are output to screen.
*********************************************************************/
void Character::fightToTheDeath(Character* enemy)
{

    if (this->strength <= 0)
	{

		std::cout << this->className << " cannot fight because it is dead." << std::endl;

		return;

	}

	else if (enemy->strength <= 0)
	{

		std::cout << enemy->className << " cannot fight because it is dead." << std::endl;

		return;

	}

	while ((this->strength >= 0) && (enemy->strength >= 0))
	{

		std::cout.flush();

		sleep(1); //1 second

		this->attack(enemy);

		if (enemy->strength <= 0)
		{

			std::cout << enemy->className << " died." << std::endl;

			enemy->isAlive = false;

			enemy->strength = 0;

			break;

		}

		std::cout.flush();

		sleep(1); //1 second

		enemy->attack(this);

		if (this->strength <= 0)
		{

			std::cout << this->className << " died." << std::endl;

			this->isAlive = false;

			this->strength = 0;

			break;

		}

	
			


	}


}


void Character::recover()
{

	std::cout << this->className << " recovered " << 2 << " strength points." << std::endl;

	this->strength = this->strength + 2;

	return ;

}

/*********************************************************************
** Function: void Character::attack(Character* enemy)
** Description: Calculates the appropriate damage dealth to enemy according to stats fo enemy
** Parameters: Character* enemy. pointer to enemy character to right
** Pre-Conditions: Enemy character is instantiated.
** Post-Conditions: Result of attack is recordied in attribute strength of enemy
*********************************************************************/
void Character::attack(Character* enemy)
{ 

	std::cout << this->className << " attacks " << enemy->className << std::endl;

	int attack;

	int defense;

	int damage;

	int damageMinusArmor;

	attack = this->returnAttack();

	defense = enemy->returnDefense();

	damage = attack - defense;

	damageMinusArmor = damage - enemy->armor;

	if(damageMinusArmor <= 0)
	{

		std::cout << "No damage caused." << std::endl;

	}

	else if (damageMinusArmor >= 0)
	{

		std::cout << damageMinusArmor << " damage caused." << std::endl; 

		enemy->strength = enemy->strength - damageMinusArmor;

	}

}

int Character::returnAttack()
{

}

int Character::returnDefense()
{

}

	
class Barbarian : public Character
{

    public:

	Barbarian();

	int returnAttack();

	int returnDefense();

};

Barbarian::Barbarian()
{

    attackPoints[0] = 2;

	attackPoints[1] = 6;

	defensePoints[0] = 2;

	defensePoints[1] = 6;

	armor = 0;

	strength = 12;

	className = "Barbarian";

}

int Barbarian::returnAttack()
{

	Dice die1(6);

	Dice die2(6);

	return (die1.rollDice() + die2.rollDice());

}

int Barbarian::returnDefense()
{

	Dice die1(6);

	Dice die2(6);

	return (die1.rollDice() + die2.rollDice());	

}

class BlueMen : public Character
{

    public:

	BlueMen();

	int returnAttack();

	int returnDefense();

};


BlueMen::BlueMen()
{

    attackPoints[0] = 2;

	attackPoints[1] = 10;

	defensePoints[0] = 3;

	defensePoints[1] = 6;

	armor = 3;

	strength = 12;

	className = "Blue Men";

}

int BlueMen::returnAttack()
{

	Dice die1(10);

	Dice die2(10);

	return (die1.rollDice() + die2.rollDice());

}

int BlueMen::returnDefense()
{

	Dice die1(6);

	Dice die2(6);
	
	Dice die3(6);

	return (die1.rollDice() + die2.rollDice() + die3.rollDice());	

}


class Goblin : public Character
{

    public:

	Goblin();

	int returnAttack();

	int returnDefense();

};

Goblin::Goblin()
{

    attackPoints[0] = 2;

	attackPoints[1] = 6;

	defensePoints[0] = 1;

	defensePoints[1] = 6;

	armor = 3;

	strength = 8;

	className = "Goblin";

}

int Goblin::returnAttack()
{

	Dice die1(6);

	Dice die2(6);

	return (die1.rollDice() + die2.rollDice());

}

int Goblin::returnDefense()
{

	Dice die1(6);

	

	return (die1.rollDice());	

}

class ReptilePeople : public Character
{

    public:

	ReptilePeople();

	int returnAttack();

	int returnDefense();

};

ReptilePeople::ReptilePeople()
{

    attackPoints[0] = 3;

	attackPoints[1] = 6;

	defensePoints[0] = 1;

	defensePoints[1] = 6;

	armor = 7;

	strength = 18;

	className = "Reptile People";

}

int ReptilePeople::returnAttack()
{

	Dice die1(6);

	Dice die2(6);

	Dice die3(6);

	return (die1.rollDice() + die2.rollDice() + die3.rollDice());

}

int ReptilePeople::returnDefense()
{

	Dice die1(6);

	return (die1.rollDice());	

}

class TheShadow : public Character
{

    public:

	TheShadow();

	int returnAttack();

	int returnDefense();

};

TheShadow::TheShadow()
{

    attackPoints[0] = 2;

	attackPoints[1] = 10;

	defensePoints[0] = 1;

	defensePoints[1] = 6;

	armor = 0; //special

	strength = 12;

	className = "The Shadow";

}

int TheShadow::returnAttack()
{

	Dice die1(10);

	Dice die2(10);

	return (die1.rollDice() + die2.rollDice());

}

int TheShadow::returnDefense()
{

	Dice die1(6);

	return (die1.rollDice());	

}



int main()
{

    //std::vector<Character*> characterVector;

	int creatureLineupSize;

	std::cout << "Assignment4." << std::endl;

	std::cout << "Player1: Choose the character lineup size for each player: " << std::endl;

	std::cin >> creatureLineupSize;

	while (std::cin.fail())
	{

		std::cout << "Invalid value. Enter again: ";
		std::cin.clear();
		std::cin.ignore(9999, '\n');
		std::cin >> creatureLineupSize;


	}

	//player 1 lineup queue
	std::queue<Character*> player1CharacterQueue;

	//player 2 lineup queue
	std::queue<Character*> player2CharacterQueue;

	//player 1 loser stack
	std::queue<Character*> player2LoserCharacterStack;

	//player 2 loser stack
	std::queue<Character*> player1LoserCharacterStack;

	for (int i = 0; i < creatureLineupSize; i++)
	{

		std::cout << "Player1: Choose a creature your your lineup: " << std::endl;

		std::cout << "1: Goblin" << std::endl << "2: Barbarian" << std::endl << "3: Reptile People" << std::endl << "4: Blue Men" << std::endl << "5: The Shadow" << std::endl;

		int choice;

		std::cin >> choice;

		if (choice == 1)
		{


			player1CharacterQueue.push(new Goblin());

		}

		else if (choice == 2)
		{

			player1CharacterQueue.push(new Barbarian());

		}


		else if (choice == 3)
		{

			player1CharacterQueue.push(new ReptilePeople());

		}


		else if (choice == 4)
		{

			player1CharacterQueue.push(new BlueMen());

		}

		else if (choice == 5)
		{

			player1CharacterQueue.push(new TheShadow());

		}



	}

	
	for (int i = 0; i < creatureLineupSize; i++)
	{

		std::cout << "Player2: Choose a creature your your lineup: " << std::endl;

		std::cout << "1: Goblin" << std::endl << "2: Barbarian" << std::endl << "3: Reptile People" << std::endl << "4: Blue Men" << std::endl << "5: The Shadow" << std::endl;

		int choice;

		std::cin >> choice;

		if (choice == 1)
		{


			player2CharacterQueue.push(new Goblin());

		}

		else if (choice == 2)
		{

			player2CharacterQueue.push(new Barbarian());

		}


		else if (choice == 3)
		{

			player2CharacterQueue.push(new ReptilePeople());

		}


		else if (choice == 4)
		{

			player2CharacterQueue.push(new BlueMen());

		}

		else if (choice == 5)
		{

			player2CharacterQueue.push(new TheShadow());

		}



	}

	while((player1CharacterQueue.size() != 0) && (player2CharacterQueue.size() != 0))
	{

		player1CharacterQueue.front()->fightToTheDeath(player2CharacterQueue.front());

		if (player1CharacterQueue.front()->isAlive == false)
		{

			//remove from queue and put on stack

			

			

			player1LoserCharacterStack.push(player1CharacterQueue.front());
			player1CharacterQueue.pop();
			

			

			player2CharacterQueue.front()->recover();

		}

		if (player2CharacterQueue.front()->isAlive == false)
		{

			//remove from queue and put on stack

			//player2LoserCharacterStack.push(player2CharacterQueue.pop());

			player2LoserCharacterStack.push(player2CharacterQueue.front());
			player2CharacterQueue.pop();

			player1CharacterQueue.front()->recover();

		}


	}

	if (player1CharacterQueue.size() == 0)
	{
		std::cout << "Player 2 wins." << std::endl;
		//player2 wins
	}

	else if (player2CharacterQueue.size() == 0) 
	{

		std::cout << "Player 1 wins." << std::endl;
		//player 1 wins

	}

	
	//std::cout << characterVector[0]->armor;

	//characterVector[0]->fightToTheDeath(characterVector[1]);

}