#include <iostream>

struct ListElement {
    int digit;
	ListElement *next;
};

void joinLast(ListElement *&l1, ListElement *&l2) {
    //getting last element of l1
    ListElement *l1tmp = new ListElement;
    l1tmp = l1->next;
    while(l1tmp->next) {
       l1tmp = l1tmp->next;
    }
    
    ListElement *l2tmp = new ListElement;
    l2tmp->digit = l1tmp->digit;
    l2tmp->next = l2;
    l2 = l2tmp;
}

int main() {
    ListElement *l1a = new ListElement;
    l1a->next = new ListElement;
    l1a->digit = 1;
    l1a->next->digit = 2;
    
    ListElement *l2a = new ListElement;
    l2a->digit = 3;
    
    joinLast(l1a,l2a);
    
    std::cout << l1a->digit << " " << l1a->next->digit << std::endl;
    std::cout << l2a->digit << " " << l2a->next->digit << std::endl;
}