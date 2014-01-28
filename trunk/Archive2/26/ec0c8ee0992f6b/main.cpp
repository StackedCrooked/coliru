//******Header File: DeckOfCards.h************
#ifndef DeckOfCards_H
#define DeckOfCards_H 

class DeckOfCards
{
    public:
		DeckOfCards();
		~DeckOfCards();
		void shuffle();
		
	
	private:
		int deck[4][13];
		
};
#endif
