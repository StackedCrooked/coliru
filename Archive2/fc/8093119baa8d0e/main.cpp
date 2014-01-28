#include <stdio.h>
enum SEMAPHORE_STATE { RED=3, YELLOW =2, GREEN=1 };
void printTrafficLightState(enum SEMAPHORE_STATE state){ //Muster Seite 5
    if (state == RED)
		printf("red\n");
	if (state == YELLOW)
			printf("yellow\n");
	if (state == GREEN)
			printf("green\n");
}
void nextTrafficLightState	(enum SEMAPHORE_STATE state){
	int i;
}
int main ()
{
	setbuf(stdout, NULL);
	enum SEMAPHORE_STATE state = RED;
	printf("Enter a state from 1 to 3 : %d");
	scanf("%d", &state);
	printTrafficLightState(state);
	nextTrafficLightState(state);
	return 0;
}