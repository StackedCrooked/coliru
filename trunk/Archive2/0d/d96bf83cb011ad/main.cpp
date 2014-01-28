#include <stdio.h>

typedef int ElementType; 
const char PRINTF_ELEMENT[] = "%d";   // %d als int dargestellt?

typedef struct{                  // Seite 11
    int data;
	struct ListNode *next;       // Pointer show next element type of data struct ListNode
}ListNode;

unsigned int sizeOfList(ListNode *list);
ListNode *insertElement(ListNode *list, unsigned int pos, int data);
void printList(ListNode *list);
int getValue(ListNode *list, unsigned int pos);
ListNode *deleteElement(ListNode *list, unsigned int pos);
void printList(ListNode *list);
int getIndexOf(ListNode *list, int data);

void freeList(ListNode *node);  //  node?
void freeList(ListNode *list);

int main() 
{     
	ListNode *list = NULL;     
	printf("Größe der Liste: %d\n", sizeOfList(list));
	list = insertElement(list, 0, 100);     
	list = insertElement(list, 0, 200);     
	list = insertElement(list, 1, 300);     
	list = insertElement(list, 3, 400);
	list = insertElement(list, 3, 500);     
	printf("Größe der Liste: %d\n", sizeOfList(list));
	printf("Listenelemente: "); 
	printList(list);     
	printf("Element an Position 1: ");
	
	printf(PRINTF_ELEMENT, getValue(list, 1)); //PRINTF_ELEMENT?
	printf("\n");
	list = deleteElement(list, 4);     
	list = deleteElement(list, 0);     
	list = deleteElement(list, 1);     
	printf("Größe der Liste: %d\n", sizeOfList(list));
	printf("Listenelemente: "); 
	printList(list);     
	printf("Position von Wert 500: %d\n", getIndexOf(list, 500));     
	freeList(list);     
	return EXIT_SUCCESS; 
	
}
