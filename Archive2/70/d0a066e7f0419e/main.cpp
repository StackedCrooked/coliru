#include <iostream>

struct ListElement {
    int value{0};
	ListElement * next{nullptr};	
};

void joinLast(ListElement *& l1, ListElement *& l2) {
	ListElement * l1tmp{nullptr};
	if(l1->next->next) {
		l1tmp = l1->next;
		while(l1tmp->next->next)
			l1tmp = l1tmp->next;
	}
	else
		l1tmp = l1;

	l1tmp->next->next = l2;
	l2 = l1tmp->next;
	l1tmp->next = nullptr;
}

void printList(ListElement *&l) {
	ListElement *tmp = l;
	while(tmp->next) {
		std::cout << tmp->value << " ";
		tmp = tmp->next; 
	}
	std::cout << tmp->value << std::endl;
}

int main() {

	ListElement *a{nullptr};
	a = new ListElement;
	a->value = 1;
	a->next = new ListElement;
	a->next->value = 2;
	a->next->next = new ListElement;
	a->next->next->value = 3;

	ListElement *b{nullptr};
	b = new ListElement;
	b->value = 5;

	printList(a);
	printList(b);

	joinLast(a,b);

	printList(a);
	printList(b);

}