//********DeckOfCards.cpp*************
#include <iostream>

using namespace std;

#include "DeckOfCards.h"

DeckOfCards::DeckOfCards()
{
    for(int row= 0; row <= 3; row++)
	{	
		for(int column = 0; column<= 12; column++)
		{
			deck[row][column] = 0;
		}
	}
	
}

DeckOfCards::~DeckOfCards(){}

void DeckOfCards::shuffle()
{
	cout <<"Hello!"<<endl;
}
