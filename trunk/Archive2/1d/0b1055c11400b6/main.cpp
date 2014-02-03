#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

class Cards
{
public:
    enum card {Ace = 1, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King};
	enum suit {Clubs, Diamonds, Hearts, Spades};

	friend ostream& operator << (ostream& os, const Cards& aCards);

	Cards(card c = Ace, suit s = Spades, bool abc = true);

	int getCards() const;

	void flipIt();

private: card z_Card;
		 suit z_Suit;
		 bool z_Up;

};
Cards::Cards (card c, suit s,bool abc): z_Card(c), z_Suit(s), z_Up(abc)
{}
int Cards::getCards()const
{
int cardValue = 0;
	if (z_Up)
	{
		cardValue = z_Card;
		if (cardValue > 10)
			cardValue = 10;
	}
	return cardValue;

}
void Cards::flipIt()
{
	z_Up = !(z_Up);
}

class Hand
{
	public:
		Hand();

		virtual ~Hand();

		void plus(Cards* pCard);
		void newHand();
		int cardsTotal() const;

	protected:
		vector<Cards*> x_Card;
};
Hand::Hand()
{
	x_Card.reserve(7);
}
Hand::~Hand()
{
	newHand();
}
void Hand::plus(Cards* pCard)
{
	x_Card.push_back(pCard);
}
void Hand::newHand()
{
	vector<Cards*>::iterator handDump = x_Card.begin();
	for (handDump =x_Card.begin(); handDump !=x_Card.end(); ++handDump)
	{
		delete *handDump;
		*handDump=0;
	}
	x_Card.clear();
}
int Hand::cardsTotal() const
{
	if(x_Card.empty())
		return 0;
	if (x_Card[0]->getCards() == 0)
		return 0;

	int handTotal = 0;
	vector<Cards*>::const_iterator handDump;

    for (handDump = x_Card.begin(); handDump != x_Card.end(); ++handDump);
	{
		handTotal += (*handDump)->getCards();
	}

	bool holdingThatAce = false;
		for (handDump=x_Card.begin(); handDump!=x_Card.end(); ++handDump);
		{
		if ((*handDump)->getCards()==Cards::Ace)
			holdingThatAce = true;
		}
	    if (holdingThatAce && handTotal <=11)

			handTotal += 10;
		
		return handTotal;
}

class PlaynPlayer : public Hand
{
	friend ostream& operator<<(ostream& os, const PlaynPlayer& aPlaynPlayer);

	public:
		PlaynPlayer(const string& name ="");

	virtual ~PlaynPlayer();
    virtual bool keepCard() const = 0;
	bool gameOver() const;
	void overItsOver() const;

	protected:
		string p_Name;

};
PlaynPlayer::PlaynPlayer(const string& name):p_Name(name)
{

}
PlaynPlayer::~PlaynPlayer()
{

}
bool PlaynPlayer::gameOver()const
{
	return(cardsTotal()>21);
}
void PlaynPlayer::overItsOver()const
{
	cout<<p_Name<<"is over 21.\n\n";
}

class humanPlayer: public PlaynPlayer
{
public:
	humanPlayer(const string& name = " ");
	virtual ~humanPlayer();
	virtual bool keepCard() const;
	void win() const;
	void loss() const;
	void newDraw() const;

};
humanPlayer::humanPlayer(const string& name):PlaynPlayer(name)
{

}
humanPlayer::~humanPlayer()
{

}
bool humanPlayer::keepCard() const
{
	cout<<p_Name<<" , another card? (Y or N): ";
	char choice;
	cin >>choice;
	return (choice == 'y' || choice == 'Y');
}
void humanPlayer::win() const
{
	cout<<p_Name<<" wins this round.\n\n";
}
void humanPlayer::loss() const
{
	cout<<p_Name<<" has lost this round.\n\n";

}
void humanPlayer::newDraw() const
{
	cout<<p_Name<<" draws another card.\n\n";
}

class comPlayer : public PlaynPlayer
{
public:
	comPlayer(const string& name="Dealer");
	virtual ~comPlayer();
	virtual bool keepCard() const;
	void firstDraw();

};
comPlayer::comPlayer(const string& name):PlaynPlayer(name)
{

}
comPlayer::~comPlayer()
{

}
bool comPlayer::keepCard() const
{
	return (cardsTotal()<=16);
}
void comPlayer::firstDraw()
{
	if (!(x_Card.empty()))
	{
		x_Card[0]->flipIt();
	}
	else
	{
		cout<<"Dealer has ended game.\n\n";
	}

}

class cardDeck : public Hand
{
public:
	cardDeck();
	virtual ~cardDeck();
	void dealCards();
	void shuffleCards();
	void dealHand(Hand& aHand);
	void addToHand(PlaynPlayer& aPlaynPlayer);
};
cardDeck::cardDeck()
{
	x_Card.reserve(52);
	dealCards();
}
cardDeck::~cardDeck()
{

}
void cardDeck::dealCards()
{
	newHand();
	for (int v = Cards::Clubs; v <=Cards::Spades; ++v)
	{
			for (int x = Cards::Ace; x <=Cards::King; ++x)
			{
			plus(new Cards(static_cast<Cards::card>(x), static_cast<Cards::suit>(v)));
			}
	}
}
void cardDeck::shuffleCards()
{
random_shuffle(x_Card.begin(), x_Card.end());
}
void cardDeck::dealHand(Hand& aHand)
{
	if (!x_Card.empty())
	{
		aHand.plus(x_Card.back());
		x_Card.pop_back();
	}
	else
		cout <<"It's the end of the deck, wait...";
}
void cardDeck::addToHand(PlaynPlayer& aPlaynPlayer)
{
	cout<<endl;
	while(!(aPlaynPlayer.gameOver())&& aPlaynPlayer.keepCard())
	{
		dealHand(aPlaynPlayer);
		cout<<aPlaynPlayer<<endl;

		if (aPlaynPlayer.gameOver())
		{
			aPlaynPlayer.overItsOver();
		}
	}
}

class jackedBlack
{
public:
	jackedBlack(const vector<string>& name);
	~jackedBlack();
	void playTime();

private:
	cardDeck a_cardDeck;
	comPlayer a_comPlayer;
	vector<humanPlayer> a_humanPlayer;
};
jackedBlack::jackedBlack (const vector<string>& names)
{
	vector<string>::const_iterator plyrName;

	for (plyrName=names.begin(); plyrName!=names.end(); ++plyrName)
	{
		a_humanPlayer.push_back(humanPlayer(*plyrName));
	}
	srand(static_cast<unsigned int>(time(0)));
	a_cardDeck.dealCards();
	a_cardDeck.shuffleCards();
}
jackedBlack::~jackedBlack()
{

}
void jackedBlack::playTime()
	{
	vector<humanPlayer>::iterator plyrPlayer;
	
	for (int d = 0; d < 2; ++d)
	{
		for(plyrPlayer=a_humanPlayer.begin();plyrPlayer!=a_humanPlayer.end();++plyrPlayer)
		{
			a_cardDeck.dealHand(*plyrPlayer);
		}
		a_cardDeck.dealHand(a_comPlayer);
	}
	a_comPlayer.firstDraw();

	for (plyrPlayer= a_humanPlayer.begin(); plyrPlayer!=a_humanPlayer.end();++plyrPlayer)
	{
		cout<<*plyrPlayer<<"\n\n";
	}

	cout<<a_comPlayer<<"\n\n";

	for (plyrPlayer=a_humanPlayer.begin();plyrPlayer!=a_humanPlayer.end();++plyrPlayer)
    {
		a_cardDeck.addToHand(*plyrPlayer);
	}

	a_comPlayer.firstDraw();
	cout<<endl<<a_comPlayer;

	a_cardDeck.addToHand(a_comPlayer);

	if(a_comPlayer.gameOver())
	{
		for (plyrPlayer=a_humanPlayer.begin();plyrPlayer!=a_humanPlayer.end();++plyrPlayer)
		{
			if(!(plyrPlayer->gameOver()))
			{
				plyrPlayer->win();
			}	
		}
	}
	else
	{
		for(plyrPlayer=a_humanPlayer.begin(); plyrPlayer!=a_humanPlayer.end();++plyrPlayer)
		{
			if (!(plyrPlayer->gameOver()))
			{
				if(plyrPlayer->cardsTotal()>a_comPlayer.cardsTotal())
					plyrPlayer->win();
			
				else if(plyrPlayer->cardsTotal()<a_comPlayer.cardsTotal())
				plyrPlayer->loss();
				else
				plyrPlayer->newDraw();
			}
		}
	}
	for(plyrPlayer=a_humanPlayer.begin();plyrPlayer!=a_humanPlayer.end();++plyrPlayer)
	{
		plyrPlayer->newHand();
	}
	a_comPlayer.newHand();
}

ostream& operator<<(ostream& os, const Cards& aCards);
ostream& operator<<(ostream& os, const PlaynPlayer& aPlaynPlayer);

int main()
{
	cout <<"\t\t Welcome to my version of Blackjack; Jackedblack.\n\n";
	int plyrNumber=0;
	while (plyrNumber<1||plyrNumber>7)
	{
		cout<<"Player count? (1-7): ";
		cin>>plyrNumber;
	}
	vector<string>names;
	string name;
	for (int q=0;q<plyrNumber;++q)
	{
		cout<<"What's your name? ";
		cin>>name;
		names.push_back(name);
	}
	cout<<"\n\n";
	jackedBlack zjackedBlack(names);
	char choice = 'y';
	while(choice !='n' && choice !='N')
	{
		zjackedBlack.playTime();
		cout<<"\n\n Do you want to play again (Y or N)?";
		cin>>choice;
	}
		return 0;
}
ostream& operator<<(ostream& os, const Cards& aCards)
{
	const string Z_CARD[]={"0","A","2","3","4","5","6","7","8","9","10","J","Q","K"};
    const string Z_SUIT[]={"C","D","H","S"};
	if(aCards.z_Up)
		os<<Z_CARD[aCards.z_Card]<<Z_SUIT[aCards.z_Suit];
	else
		os<<"??";
	return os;
}
ostream& operator<<(ostream& os, const PlaynPlayer& aPlaynPlayer)
{
	os<<aPlaynPlayer.p_Name<<" \t";
	vector<Cards*>::const_iterator plyrCard;
	if (!aPlaynPlayer.x_Card.empty())
	{
		for (plyrCard = aPlaynPlayer.x_Card.begin(); plyrCard != aPlaynPlayer.x_Card.end(); ++plyrCard)
		{
			os<<*(*plyrCard)<<"\t";
		}
		if(aPlaynPlayer.cardsTotal()!=0)
		
			cout<<"("<<aPlaynPlayer.cardsTotal()<<")";
		
	}
		else
			os<<"<empty>";
	
		return os;
	
}
