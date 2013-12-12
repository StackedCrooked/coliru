#include <iostream>

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
	print(list);
	appendList(list, 5);
	print(list);
	appendList(list, 6);
	print(list);
	appendList(list, 3);
	print(list);
	appendList(list, 5);
	print(list);
	cleanup(list);
	print(list);
}

struct StackElement {
    StackElement * next;
	int digit;
};

StackElement * stack;

void create() {//brilliant function
	stack = nullptr;
}

bool isEmpty() {
	return stack == nullptr;
}

void push(int value) {
	stack = new StackElement{stack, value};//list initialization of struct
}

void pop() {
	if (stack != nullptr) {
		StackElement * help = stack;//backup original top-of-stack-address
		stack = stack->next;//reset top-of-stack to the second element
		delete help;//delete the – now unused – previous top-of-stack
	}
}

int top() {
	return stack->digit;
}

void print() {
	if (isEmpty())
		std::cout << "Stack ist leer" << std::endl;
	else {
		std::cout << "oberstes Element: " << top() << std::endl;
		StackElement * help = stack;
		std::cout << "{";
		while (help != nullptr) {
			std::cout << help->digit << " ";
			help = help->next;
		}
		std::cout << "}" << std::endl;
	}
}

void cleanup() {//delete all new’ed instances
	while (!isEmpty())
		pop();
}

void stackTest() {
	create();
	print();
	push(5);
	print();
	push(3);
	print();
	pop();
	print();
	push(6);
	print();
	pop();
	top();
	print();
	cleanup();
	print();
}

int main() {
    linkedListTest();
    stackTest();
}