  #include <iostream>
using namespace std;

template <class T>
class List
{
public:
    List();
	List(int insize);
	~List();
	T get(int index) const;
	void add(T value);
	int getSize() const;
	void remove(int index);
private:
	int aindex;
	T *listarray;
	int size;
};
/*--------------------------Constructs and Destructs------------------------*/
template <class T>
List<T>::List()
{
	size = 10;
	aindex = 0;
	listarray = new T[size];
}

template <class T>
List<T>::List(int insize):size(insize)
{
	aindex = 0;
	listarray = new T[insize];
}

template <class T>
List<T>::~List()
{
	delete [] listarray;
	size = 0;
}
/*--------------------------Get-------------------------*/
template <class T>
int List<T>::getSize() const 
{
	//return size;
    return aindex;
}
/*----------------------Add your code here!!!! -------------*/
/*---- add---*/
/* adds a value to array at end.  
If array is too small, make bigger (size you need +10) new array copy
delete old array
*/
template <class T>
void List<T>::add(T value)
{
	if(aindex < size)
	{
		listarray[aindex] = value;
		aindex++;
	}
	else
	{
		T *temparray = new T[size+10];
		for(int i = 0; i < size; i++)
		{
			temparray[i] = listarray[i];
		}
		size = size+10;
		temparray[aindex] = value;
		aindex++;
		delete [] listarray;
		listarray = temparray;
	}

}
/*-----get---*/
/*return value at position given
*/
template <class T>
T List<T>::get(int index) const
{
	if((index > -1) && (index < aindex))
	{
		return listarray[index];
	}
	else
	{
		return -1;
	}
}

/*------remove----*/
/*Remove value at position
Just zero if at end.
If in middle, make zero and copy all above down to fill in slots
*/

template <class T>
void  List<T>::remove(int index)
{
	if(index == (aindex-1))
	{
		listarray[index] = 0;
		aindex--;
	}
	else if(index < aindex)
	{
		listarray[index] = 0;
		for(int i = index; i < (aindex-1); i++)
		{
			listarray[i] = listarray[i+1];
		}
        --aindex;
	}
	else
	{
		return;
	}

}

int main()
{
	
	List<int> *mylist = new List<int>(1);
	mylist->add(10);
	mylist->add(15);
	mylist->add(20);
	cout << "Added three values\n";
	cout << mylist->get(0) << " " << mylist->get(1) << " " << mylist->get(2) <<endl;
    mylist->remove(1);
	cout << mylist->get(0) << " " << mylist->get(1) << " " << mylist->get(2) <<endl;
    delete mylist;
}
