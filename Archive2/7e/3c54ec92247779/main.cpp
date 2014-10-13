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
	};

	Node* begin_;
	Node* node_;
	Node* end_;
	size_t size_;

	LinkedList(): 
		begin_(new Node()),
		node_(new Node()),
		end_(new Node()),
		size_(0)
	{
		cout << "LinkedList()" << endl;
	};
	
	LinkedList(const LinkedList &copy) :
		begin_(copy.begin),
		end_(copy.end),
		size_(copy.size)
	{
		cout << "LinkedList(const LinkedList<T> &copy)" << endl;
	}
	
	~LinkedList()
	{
		delete begin_;
		delete node_;
		delete end_;
	}
	
    LinkedList<T> pushBack(const T &value)
	{
		if (size_ == 0)
		{
			whenPushToEmpty(value);
		}
		else
		{
			node_ = end_;
			end_ = new Node();

			node_->next = *end_;
			end_->prev = *node_;
			end_->next = NULL;
			end_->value = value;
		}
		++size_;

		return *this;
	}

	LinkedList<T> pushFront(const T &value)
	{
		if (size_ == 0)
		{
			whenPushToEmpty(value);
		}
		else
		{
			node_ = begin_;
			begin_ = new Node();

			node_->prev = *begin_;
			begin_->next = *node_;
			begin_->prev = NULL;
			begin_->value = value;
		}
		++size_;
		return &this;
	}

	void popBack()
	{

	}

	void popFront()
	{

	}

	void whenPushToEmpty(const T &value)
	{
		node_->next = NULL;
		node_->prev = NULL;
		node_->value = value;

		begin_ = node_;
		end_ = node_;

		//cout << begin_->value << '==' << node_->value << '==' << end_->value << endl;
	}

	const T getValue()
	{
		return node_.value;
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
	LinkedList<size_t> ill();
	//ill->pushBack(1)->pushBack(2);
	/*for (;ill1->hasNext();ill1->next())
	{
		cout << ill1->getValue() << endl;
	}*/


	//ill1->pushBack(1)->pushBack(2);

	return 0;
}