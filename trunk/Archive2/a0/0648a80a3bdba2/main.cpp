#include <iostream>
#include <stdexcept>

struct linkedNodes {
private:
    struct node {
		node * next;
		const int value;
	};
	node * firstNode = nullptr;//start with no nodes
public:
	~linkedNodes() {//delete’s all nodes on scope exit
		while (!isEmpty())
			pop();
	}
	void append(int newDigit) {
		if (isEmpty())//create first element if not present
			push(newDigit);
		else {//walk through to the end of the list and append
			node * help = firstNode;//we dont want to modify head-of-nodes
			while (help->next != nullptr)//walk through nodes
				help = help->next;
			help->next = new node{nullptr, newDigit};//list initialization of struct
		}
	}
	bool isEmpty() const {
		return firstNode == nullptr;
	}
	void push(int value) {
		firstNode = new node{firstNode, value};//list initialization of struct
	}
	void pop() {
		if (!isEmpty()) {
			node * const help = firstNode->next;//backup original head-of-nodes-address
			delete firstNode;//reset head-of-nodes to the second element
			firstNode = help;//delete the – now unused – previous top-of-stack
		}
	}
	void print() const {
		if (isEmpty())
			std::cout << "Nodes leer" << std::endl;
		else {
			std::cout << "oberstes Element: " << firstNode->value << std::endl;
			node * help = firstNode;
			std::cout << "{";
			while (help != nullptr) {
				std::cout << help->value << " ";
				help = help->next;
			}
			std::cout << "}" << std::endl;
		}
	}
	int top() const {
		if (!isEmpty())
			return firstNode->value;
        else throw std::runtime_error("linkedNodes::top() called with no nodes");
	}
};

int main() {
	linkedNodes s;
	s.print();
	s.push(6);
	s.print();
	s.pop();
	s.print();
	s.push(6);
	s.push(5);
	s.push(3);
	s.print();
	s.append(9);
	s.print();
	s.pop();
	s.print();
}
