#include <iostream>
#include <string>

struct Node
{
    std::string data;
	Node *link;
};


void works(Node* &head)
{
	Node *temp;
	Node *tail;

	temp = head; //head is initialized to point at the first node in the list.     

	for (tail = head; tail->link != NULL; tail = tail->link)
	{
		;
	}
	//Sets tail pointer to the last node in the list

	head = head->link; //sets head to the second node/new first node
	tail->link = temp; //sets the link field of what tail points at to what temp points at
	temp->link = NULL; //sets the last node to point at NULL
}


void prepend(std::string i, Node* &head)
{
	Node *n = new Node{ i, head };
	head = n;
}

void print(Node *n)
{
	while (n)
	{
		std::cout << n->data;
		n = n->link;
	}
	std::cout << '\n';
}

void add(Node *& head, std::string data)
{
	if (head)
	{
		Node *temp = head;
		Node *last;
		while (temp)
		{
			last = temp;
			temp = temp->link;
		}
		last->link = new Node{ data, NULL };
	}
	else
		prepend(data, head);
}


	int main()
	{
		Node *head = new Node{ "Charlie", NULL };
		add(head, "Lisa");
		add(head, "Drew");
		add(head, "Derrick");
		add(head, "AJ");
		add(head, "Bojian");
		print(head);
		works(head);
		print(head);
	}