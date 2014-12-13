
#pragma once
#ifndef LIST_H
#define LIST_H

template <typename T>
class List
{
    class Node
	{
	public: 
		T _data;
		Node* _next;
	};
	Node* _head;
	Node* _last;
	Node* _actual;
	unsigned int _count;

	bool insertFirst(const T& prvek)
	{
		if (_head == nullptr)
		{
			Node* node = new Node();
			node->_data = prvek;
			node->_next = node;
			_head = node;
			_last = node;
			_actual = node;
			_count++;
			return true;
		}
		else
			return false;
	}

	Node* findPrevious(const Node& node);
public:
	typedef void(*UkFunkce)(T);
	List(void)
	{
		_head = nullptr;
		_last = nullptr;
		_actual = nullptr;
		_count = 0;
	}

	~List(void)
	{
		while (_head != _last)
		{
			Node* oldNode = _head;
			_head = _head->_next;
			delete oldNode;
		}
		delete _last;
		_head = nullptr;
		_last = nullptr;
		_actual = nullptr;
	}
	bool JePrazdny(void)const;
	int PocetPrvku() const;
	void VlozPrvni(const T&);
	void VlozPosledni(const T&);
	void VlozNaslednika(const T&);
	T& ZpristupniAktualni(void);
	T& ZpristupniPrvni(void);
	T& ZpristupniPosledni(void);
	T& ZpristupniNaslednika(void);
	T OdeberPrvni(void);
	T OdeberPosledni(void);
	T OdeberAktualni(void);
	T OdeberNaslednika(void);
	void Prohlidka(UkFunkce) const;
	void Zrus(void);
	class const_iterator;

	const_iterator cbegin();
	const_iterator cend();

	class iterator
	{
		Node* _node;
	public:
		iterator(Node* node) : _node(node){}
		~iterator(){ _node = nullptr; }

		iterator& operator=(const iterator& other)
		{
			_node = other._node;
			return *this;
		}
		//bool operator==(const iterator& other)
		//{
		//	if (_node == nullptr || other._node == nullptr)
		//	{
		//		return false;
		//	}
		//	else
		//	{
		//		return _node->_data == other._node->_data;
		//	}
		//}
		bool operator==(const iterator& other) { return _node == other._node; }
		bool operator!=(const iterator& other) { return !((*this) == other); }

		/*bool operator!=(const iterator& other)
		{
			if (_node == nullptr || other._node == nullptr)
			{
				return false;
			}
			else
			{
				return _node->_data != other._node->_data;
			}
		}*/

		iterator& operator++() // prefix
		{
			if (_node != nullptr)
			{
				_node = _node->_next;
			}
			return *this;
		}
		iterator operator++(int) // postfix
		{
			iterator temp(*this);
			++(*this);
			return temp;
		}
		T& operator*() // dereference
		{
			return _node->_data;
		}
		T* operator->() // šipková notace
		{
			return &*(List<T>::iterator)*this;
		}
	};

	iterator begin()
	{
		return iterator(_head);
	}

	iterator end()
	{
		return iterator(nullptr);
	}
};

template <typename T>
typename List<T>::Node* List<T>::findPrevious(const Node& node)
{
	return nullptr;
}

template <typename T>
bool List<T>::JePrazdny() const
{
	return _head == nullptr;
}

template <typename T>
int List<T>::PocetPrvku() const
{
	return _count;
}

template <typename T>
void List<T>::VlozPrvni(const T& prvek)
{
	if (!insertFirst(prvek))
	{
		Node* novy = new Node();
		novy->_data = prvek;
		novy->_next = _head;
		_head = novy;
		_last->_next = _head;
		_actual = novy;
		_count++;
	}
}

template <typename T>
void List<T>::VlozPosledni(const T& prvek)
{
	if (!insertFirst(prvek))
	{
		Node* oldLast = _last;
		Node* newLast = new Node();
		newLast->_data = prvek;
		newLast->_next = _head;
		_last = newLast;
		oldLast->_next = newLast;
		_actual = _last;
		_count++;
	}
}

template <typename T>
void List<T>::VlozNaslednika(const T& prvek)
{
	if (!insertFirst(prvek))
	{
		Node* newLast = new Node();
		newLast->_data = prvek;
		newLast->_next = _actual->_next;
		_actual->_next = newLast;
		_actual = newLast;
		_count++;
	}
}

template <typename T>
T& List<T>::ZpristupniAktualni()
{
	return _actual->_data;
}

template <typename T>
T& List<T>::ZpristupniPrvni()
{
	_actual = _head;
	return _head->_data;
}

template <typename T>
T& List<T>::ZpristupniPosledni()
{
	_actual = _last;
	return _last->_data;
}

template <typename T>
T& List<T>::ZpristupniNaslednika()
{
	_actual = _actual->_next;
	return _actual->_data;
}

template <typename T>
T List<T>::OdeberPrvni()
{
	Node* node = _head;
	T element = _head->_data;
	_head = _head->_next;
	_last->_next = _head;
	delete node;
	_count--;
	return element;
}

template <typename T>
T List<T>::OdeberAktualni() // not completed
{
	Node* node = _actual;
	T element = _actual->_data;
	_actual = _actual->_next;
	_last->_next = _head;
	delete node;
	_count--;
	return element;
}

template <typename T>
void List<T>::Prohlidka(UkFunkce function) const
{
	Node* node = _head;
	do
	{
		function(node->_data);
		node = node->_next;
	} while (node != _head);
}
#endif