// programming assignment #2: Stack - using STL vector as the underlying data store
#include <iostream>
using namespace std;

template <class T>
class mystack {
public:
    mystack();
	// postcondition: data member n is initialized to 0
	void push(T *obj);
	//  precondition: T type obj is passed to the function by reference
	// postcondition: obj is pushed onto the back of vector stk
	bool pop();
	//  precondition: stk is must not be empty
	// postcondition: obj on top of the stack is popped (removed)
	T top();
	//  precondition: the stack must not be empty
	// postcondition: the obj on top of the stack is returned
	int getSize();
	// postcondition: $ of objects on stack is returned
	bool empty();
	// postcondition: return true if stack is empty; false otherwise
private:
	int n;			// # of objects on stack; 0 is stack is empty
	T arr[5];	// data store for objects
};

template <class T>
mystack<T>::mystack()
{
	n = 0;
}

template <class T>
void mystack<T>::push(T *obj )
{
	arr[n] = obj[n];
	++n;
}

template <class T>
bool mystack<T>::pop()
{
	if(empty())
	{
		cout << "Error the stack is currently empty: " << n << endl;
		return 0;
	}
	else
	{
		n--;
		cout << " popped\n";
		return 1;
	}
}

template <class T>
T mystack<T>::top()
{
	if(empty())
	{
		cout << "Error Stack Is Empty!..\n";
		return 0;
	}
	else 
	{
		return (arr[n-1]);
	}
}

template<class T>
int mystack<T>::getSize()
{
	return n;
}

template <class T>
bool mystack<T>::empty()
{
	return (n==0);
}

int main()
{
    mystack<int> newest;
	int pushings[] = {1,2,3,4,5};
	for(int i = 0; i < 5; i++)
	{
		newest.push(pushings);
		cout << newest.top() << endl;
	}

	cout << "\n\nCurrent Size:" << newest.getSize() << " Top: " << newest.top() << endl << endl;

	for(int top = 4; top >= 0; top--)
	{
		cout << newest.top();
		newest.pop();
	}

	cout << endl << endl << "Size: " << newest.getSize() << " = 0;" <<  endl;
	return 0;

}