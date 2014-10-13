// LinkedList.cpp : Defines the entry point for the console application.
//
//#include "stdafx.h"
#include <stdio.h>
#include <iostream>

using namespace std;

template<class T>
struct LinkedList 
{
    struct Node
	{
		Node* next;
		Node* prev;
		T value;
		

		Node() :
			next(NULL), 
			prev(NULL), 
			value(0)
		{
			cout << "Node()" << endl;
		}
		Node(const T& value) :
			next(NULL),
			prev(NULL),
			value(value)
		{
			cout << "Node(const T &value)" << endl;
		}
		Node(const Node &node) :
			next(node.next),
			prev(node.prev),
			value(node.value)
		{
			cout << "Node(const Node<T> &node)" << endl;
		}
		~Node
		{
			next = NULL;
			prev = NULL;
		}

	};

	Node* begin;
	Node* node;
	Node* end;
	int size;

	LinkedList(): 
		begin(new Node()),
		node(new Node()),
		end(new Node()),
		size(0)
	{
		cout << "LinkedList()" << endl;
	};

	
	
	LinkedList(const LinkedList &copy) :
		begin(copy.begin),
		end(copy.end),
		size(copy.size)
	{
		cout << "LinkedList(const LinkedList<T> &copy)" << endl;
	}

	~LinkedList()
	{
		delete begin;
		delete node;
		delete end;
	}
	
	void pushBack(const T &value)
	{
		if (size == 0)
		{
			whenPushToEmpty(value);
		}
		else
		{
			node = end;
			end = new Node();

			node->next = *end;
			end->prev = *node;
			end->next = NULL;
			end->value = value;
		}
		++size;
	}

	void pushFront(const T &value)
	{
		if (size == 0)
		{
			whenPushToEmpty(value);
		}
		else
		{
			node = begin;
			begin = new Node();

			node->prev = *begin;
			begin->next = *node;
			begin->prev = NULL;
			begin->value = value;
		}
		++size;
	}

	/*void popBack()
	{

	}

	void popFront()
	{

	}*/

	void whenPushToEmpty(const T &value)
	{
		node->next = NULL;
		node->prev = NULL;
		node->value = value;

		begin = node;
		end = node;

		//cout << begin->value << '==' << node->value << '==' << end->value << endl;
	}

	bool hasNext()
	{
		return node->next != 0;
	}

	bool hasPrev()
	{
		return node->prev != 0;
	}

	bool next()
	{
		boolean has = hasNext();
		if (has)
		{
			node = node->prev;
			return true;
		}
		return has;
	}

	bool prev()
	{
		boolean has = hasPrev();
		if (has)
		{
			node = node->prev;
		}
		return has;
	}

	void begin()
	{
		node = begin;
	}

	void end()
	{
		node = end;
	}

	const T getValue()
	{
		return node.value;
	}


	/*
	void pushFront(const T &value)
	{

	}
	*/

	/*
	&size_t size()
	{
		return this.size;
	}
	*/

};

int main(int argc, char* argv[])
{
	LinkedList<int>* ill1;
	LinkedList<int>* ill2;
	//size_t listSize;

	ill1 = new LinkedList<int>();
	ill1->pushBack(2);
	ill1->pushFront(1);
	ill1->begin();
	for (;ill1->hasNext();ill1->next())
	{
		cout << ill1->getValue() << endl;
	}

	ill2 = new LinkedList<int>(*ill1);
	//ill1->pushBack(1)->pushBack(2);

	//cout << "Mennyi erteket akar megadni?" << endl;
	//cin >> listSize;
	//cout << "A beirt szam: " << listSize << endl;

	delete ill1;
	delete ill2;

	return 0;
}