// Writen by Raj Chaugule
// used to count the number of rounds needed to restore a deck of cards to 
// origninal for.
// Takes argument - number of card on command line. 
// Prints final output - number of rounds. 
// If debug output and all the moves are needed then enable printf macro below at line 13.

#include <stdio.h>
#include <stdlib.h>

//Code to compile out debug prints
// To enable debug prints set this to 0.
// Currently set to 1 to print only final output.
#if 0
#define printf( a, ... )
#else
#define printf( a, ... ) printf( a,  ##__VA_ARGS__ )
#endif

typedef struct card {
    int card_type;
	struct card * next;
} Card;


typedef struct deck_of_cards {
	Card* head;
	Card* tail;
} Deck_of_cards;


Deck_of_cards* init_deck_of_cards( int number_of_cards )
{
	Card * head = NULL;
	Card * current_node = NULL;
	int count = 0;
	for (count = 0; count < number_of_cards; count++) {
		Card * tmp = (Card*) calloc(sizeof(Card), 1);
		tmp->card_type = count;
		//printf("Creating card: %d\n", count);
		if (count == 0) {
			head = tmp;
			current_node = tmp;
		}
		else {
			current_node->next = tmp;
			current_node = tmp;
		}
	}
	current_node->next = NULL;
	
	Deck_of_cards* deck = (Deck_of_cards*) calloc(sizeof(Deck_of_cards), 1);
	deck->head = head;
	deck->tail = current_node;
	
	return deck;
}

void print_deck(Deck_of_cards* deck)
{
	Card * deck_head = deck->head;
	//printf("The cards are: \n");
	while (deck_head != NULL)
	{
		printf("%d\n",deck_head->card_type);
		deck_head = deck_head->next;
	}
}


int move_top_card_to_table(Deck_of_cards** orig_deck, Deck_of_cards** deck_on_table)
{
	//printf("The head is : %d\n",(*orig_deck)->head->card_type);
	//printf("The tail is : %d\n",(*orig_deck)->tail->card_type);
	Card * tmp = NULL;
	
	//Hand deck exhausted - end of round
	if ((*orig_deck)->head == NULL) {
		printf("To table: Hand Deck Exhausted\n");
		return 0;
	}

	// Update tail if needed - ie this is the last card on the deck
	if ((*orig_deck)->head->next == NULL) {
		(*orig_deck)->tail = NULL;
	}

	//This is the first card to go on the table	
	if ( (*deck_on_table)->head == NULL ) { 
		(*deck_on_table)->head = (*orig_deck)->head;
		(*orig_deck)->head = (*orig_deck)->head->next;
		(*deck_on_table)->head->next = NULL;
		// Update tail to this card. - only done for the first card put on the table. [Bug 1]
		(*deck_on_table)->tail = (*deck_on_table)->head;
	}	
	else { // Insert the card at the head always.
		tmp = (*deck_on_table)->head; 
		(*deck_on_table)->head = (*orig_deck)->head;
		(*orig_deck)->head = (*orig_deck)->head->next;
		(*deck_on_table)->head->next = tmp;
	}
	
	printf("To table: Card Moved: %d\n",(*deck_on_table)->head->card_type);
	return 1;
}


int move_card_back_of_deck(Deck_of_cards** orig_deck)
{	
	if ((*orig_deck)->head == NULL ) {
		printf("To back: Hand Deck Exhausted\n");
		return 0;
	}	
	// If this is the last card in the deck. return 1;
	if ((*orig_deck)->head->next == NULL ) {
		printf("To back: Hand Deck Only one card left\n");
		return 1;
	}
	else {
		(*orig_deck)->tail->next = (*orig_deck)->head;
		(*orig_deck)->head = (*orig_deck)->head->next;
		(*orig_deck)->tail = (*orig_deck)->tail->next;
		(*orig_deck)->tail->next = NULL;
		printf("To back: Card Moved: %d\n",(*orig_deck)->tail->card_type);
		return 1;
	}
}

int comparator(Deck_of_cards** orig_deck)
{
	if ((*orig_deck)->head == NULL ) {
		printf("Comparator: Hand Deck Exhausted\n");
		return 0;
	}
	int running_count = 0;
	Card* card_it = (*orig_deck)->head;
	do {
		if (card_it->card_type != running_count) {
			return 0;
		}
		running_count++;
		card_it = card_it->next;
	} while ( card_it != NULL ); 
	return 1;
}

void move_deck_table_to_hand(Deck_of_cards** orig_deck, Deck_of_cards** deck_on_table)
{
	(*orig_deck)->head = (*deck_on_table)-> head;
	(*orig_deck)->tail = (*deck_on_table)-> tail;
	(*deck_on_table)-> head = NULL;
	(*deck_on_table)-> tail = NULL;
}



int main(int argc, char* argv[])
{
	int num_of_cards = 0;	
	int rounds = 0;
	printf("The program started \n");
	num_of_cards = atoi(argv[1]);
	printf("The number of cards in the initial deck is: %d\n", num_of_cards);
	
	if (num_of_cards == 0 || argc == 1) {
		printf ("Error: Enter the number of cards in the orig deck... \n");
		return 0;
	}
	
	
	Deck_of_cards* orig_deck;
	orig_deck = init_deck_of_cards(num_of_cards);
	
	Deck_of_cards* deck_on_table = (Deck_of_cards*)calloc(sizeof(Deck_of_cards), 1);
	deck_on_table->head = NULL;
	deck_on_table->tail = NULL;

	printf("The Hand Deck is: \n");
	print_deck(orig_deck);
	printf("The table Deck is: \n");
	print_deck(deck_on_table);

	
	do {
		printf("Starting round:%d ..... \n",rounds);
		printf("===============================================\n");
		while (move_top_card_to_table(&orig_deck, &deck_on_table))
		{
			if (!move_card_back_of_deck(&orig_deck)) {
				break;
			}
		}
		printf("===============================================\n");
		printf("Ending round:%d ..... \n",rounds);
		
		printf("The Hand Deck is: \n");
		print_deck(orig_deck);
		printf("The table Deck is: \n");
		print_deck(deck_on_table);
		move_deck_table_to_hand(&orig_deck, &deck_on_table);
		rounds++;
	} while (!comparator(&orig_deck));

	char * output_to_stdio = (char*)calloc(sizeof(char),75);
	sprintf(output_to_stdio, "The number of rounds to accomplish the orig state: %d", rounds);
	//print_deck(orig_deck);
	puts(output_to_stdio);	
	return 0;
}
