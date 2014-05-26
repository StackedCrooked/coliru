#include <iostream>
#include <string>

using namespace std;

template <class t_type>
class TLIST
{

public:

    TLIST();
	~TLIST();
	TLIST( const TLIST<t_type> &); // *** const added
	bool IsEmpty();
	bool IsFull();
	int Search(t_type);
	void Double_Size();
	void Add(t_type item);
	void Remove(const t_type org);
	TLIST<t_type> & operator=(const TLIST<t_type> & org) ;

	TLIST<t_type> & operator+=(const t_type & org);

	friend ostream & operator<<(ostream & out, TLIST<t_type> & org)
	{
		int i;

		for (i = 0; i<org.count; i++)
		{
			out << "DB[i" << i << "] = " << org.DB[i] << endl;
		}
		return out;
	}


private:

	t_type *DB;
	int count;
	int capacity;

};

template <class t_type>
TLIST<t_type>::TLIST()
{
	cout << "You're inside the default constructor\n";
	cout << "t_type has size of " << sizeof(t_type) << " bytes\n\n";
	count = 0;
	capacity = 2;
	DB = new t_type[capacity];

}

template <class t_type>
TLIST<t_type>::~TLIST()
{
	cout << "The destructor has been called\n";
	delete[] DB;
	count = 0;
	DB = 0;
}

template <class t_type>
TLIST<t_type>::TLIST( const TLIST<t_type> & org) // *** const added
{
	count = org.count;
	capacity = org.capacity;
	DB = new t_type[capacity];
	for (int i = 0; i<count; i++)
	{
		DB[i] = org.DB[i];
	}
}


template <class t_type>
int TLIST<t_type>::Search(t_type item)
{
	// int i;
	for (int i = 0; i < count; i++)
	{
		if (item == DB[i])
		{
			return i;
		}
		return -1;
	}
	DB = 0;
}


template <class t_type>
void TLIST<t_type>::Add(t_type item)
{
	if (count < capacity)
	{
		DB[count++] = item;
	}
	else
	{
		Double_Size();
		Add(item);
	}
}

template <class t_type>
bool TLIST<t_type>::IsEmpty()
{
    /*
	if (count == 0)
	{
		return TRUE;
	}
	return FALSE;
	*/
	return count == 0 ;
}

template <class t_type>
bool TLIST<t_type>::IsFull()
{
    /*
	if (count == capacity)
	{
		return TRUE;
	}
		return FALSE;
    */
    return count == capacity ;
}


template <class t_type>
TLIST<t_type> operator+ (TLIST<t_type> lst, const t_type & org)
{
	return lst += org;
}


template <class t_type>
void TLIST<t_type>::Double_Size()
{
	cout << endl << endl;
	cout << "Double_Size has been called\n";
	cout << "Old Size = " << capacity << endl;
	cout << "New Size = " << capacity * 2 << endl;

	capacity *= 2;
	t_type *temp = new t_type[capacity];
	for (int i = 0; i < count; i++)
	{
		temp[i] = DB[i];
	}
	delete[] DB;
	DB = temp;
}

template <class t_type>
TLIST<t_type> & TLIST<t_type>::operator=(const TLIST<t_type> & org)
{
	if (this != &org)
	{
		count = org.count;
		capacity = org.capacity;
		DB = new t_type[capacity];
		for (int i = 0; i < count; i++)
		{
			DB[i] = org.DB[i];
		}
		//return *this;
	}
	return *this ;
}

template <class t_type>
TLIST<t_type>& TLIST<t_type>::operator+= (const t_type & org)
{
	if (count < capacity)
	{
		DB[count++] = org;
		return *this;
	}
	else
	{
		Double_Size();
		return *this += org;
	}
}

// main.cpp
// #include ....

int main()
{
	TLIST<char> Char_List ;
	Char_List = Char_List + 'W' + 'E' + 'L' + 'C' + 'O' + 'M' + 'E';
	std::cout << Char_List << '\n' ;


	TLIST<int> Int_List ;
	Int_List = Int_List + 1 + 2 + 3 + 4 + 5 + 6 + 7;
	std::cout << Int_List << '\n' ;

	TLIST<string> String_List ;
	String_List = String_List + std::string("hello") + std::string("everyone") +
	                            std::string("study") + std::string("hard") +
	                            std::string("do not") + std::string("copy") +
	                            std::string("learn");
	std::cout << String_List << '\n' ;
}
