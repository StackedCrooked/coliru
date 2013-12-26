#include <iostream>
#include <stdexcept>

struct ListElement {
    ListElement * next;
	int digit;
};

void appendList(ListElement * & list, int newDigit) {
	if (list == nullptr)//create first element if not present
		list = new ListElement{nullptr, newDigit};
	else {//walk through to the end of the list and append
		ListElement * help = list;//we dont want to modify head-of-list – which was passed by reference
		while (help->next != nullptr)//walk through list
			help = help->next;
		help->next = new ListElement{nullptr, newDigit};//list initialization of struct
	}
}

void reverseList(ListElement * & current) {
    if (current == nullptr) {
        throw std::invalid_argument("reversing empty list");
    }
    ListElement * previous = nullptr;
    while (current->next != nullptr) {//valid link
        ListElement * const nextElement = current->next;//backup link
        current->next = previous;//link backwards
        previous = current;//backup current element pointer
        current = nextElement;//move forward in list
    }
    current->next = previous;//link backwards for last element/new start
}

void print(const ListElement * list) {
	if (list == nullptr)
		std::cout << "leere Liste" << std::endl;
	else {
		std::cout << "{" << list->digit << " ";
		while (list->next != nullptr) {
			list = list->next;
			std::cout << list->digit << " ";
		}
		std::cout << "}" << std::endl;
	}
}

void cleanup(ListElement * & list) {
	if (list != nullptr) {
		cleanup(list->next);//recursive cleanup
		delete list;
		list = nullptr;//after the instance is deleted, set the pointer to null to indicate it points to nothing
	}
}

void linkedListTest() {
	ListElement * list = nullptr;
    //reverseList(list);
	print(list);
	appendList(list, 5);
	print(list);
    std::cout << "↔";
    reverseList(list);
	print(list);
    appendList(list, 6);
    print(list);
    std::cout << "↔";
    reverseList(list);
	print(list);
	appendList(list, 3);
	print(list);
	appendList(list, 4);
	print(list);
    std::cout << "↔";
    reverseList(list);
    print(list);
	cleanup(list);
	print(list);
}

int main() {
    linkedListTest();
}