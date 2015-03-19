#include <iostream>
#include <string>

using namespace std;

class Contact
{
	friend std::ostream& operator<<(std::ostream& os, const Contact& c);
	friend class ContactList;

public:
	Contact(std::string name = "none");

private:
	std::string name; 
	Contact* next;
};

Contact::Contact(string n)
    : name(n)
	, next(NULL)
{}

ostream& operator<<(ostream& os, const Contact& c)
{
	return os << "Name: " << c.name;
}


class ContactList
{
public:
    ContactList();

	void addToHead(const std::string&);
	void printList();
	void insert(const std::string&);


private:
	Contact* head;
	int size;

};


ContactList::ContactList()
    : head(NULL)
	, size(0)
{}


void ContactList::addToHead(const string& name)
{
	Contact* newOne = new Contact(name);

	if (head == NULL)
	{
		head = newOne;
	}
	else
	{
		newOne -> next = head;
		head = newOne;
	}
	size++;

}

void ContactList::printList()
{
	Contact* tp = head;
	while (tp != NULL)
	{
		cout << *tp << endl;
		tp = tp->next;
	}
}

void ContactList::insert(const string& name)
{
	Contact*   newNode = new Contact(name);

	if (head == 0)
	{
		head = newNode;
	}
	else
	{
		Contact* curr = head;
		Contact* prev = NULL;
		while (curr != NULL)
		{
			if (curr->name >= newNode->name)
			{
				break;
			}
			else
			{
				prev = curr;
				curr = curr->next;
			}
		}
		
		if (curr == head)
		{
			newNode->next = head;
			head = newNode;\
		}
		else
		{
			newNode->next = curr;
			prev->next = newNode;
		}
	}
	size++;
}



int main()
{
	ContactList* cl1 = new ContactList();

	string name;
	while (true)
	{
		cout << "Enter the name of the contact or 'q' to quit." << endl;
		cin >> name;
		if (name == "q")
			break;
		cl1->insert(name);
	}

	cl1->printList();

	return 0;
}