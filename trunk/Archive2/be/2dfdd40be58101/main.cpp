#include <iostream>
#include <forward_list>
#include <iterator>

using namespace std;

template <typename T> void printList(const forward_list<T> &listRef);

int main()
{
	forward_list<int> list;

	list.push_front(8);
	list.push_front(7);
	list.push_front(5);
	list.push_front(9);
	list.push_front(0);
	list.push_front(1);
	list.push_front(3);
	list.push_front(2);
	list.push_front(6);
	list.push_front(4);
 
    cout << "before:     "; 
	printList(list);
    list.sort();
    cout << "\nascending:  ";
	printList(list);
    list.reverse();
    cout << "\ndescending: ";
	printList(list);

	return 0;
}

template <typename T> void printList(const forward_list<T> &listRef)
{
	if (listRef.empty())
		cout<<"List is empty";
	else
	{
		ostream_iterator<T> output(cout, " ");
		copy(listRef.begin(), listRef.end(), output);
	}
}