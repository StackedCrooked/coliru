#include <iostream>

template<typename T>
struct node
{
    T data;
	node *next;

	explicit node(T&& d = T{}, node *n = nullptr) :
		data(std::move(d)), next(n) { }

	explicit node(const T& d, node *n = nullptr) :
		data(d), next(n) { }
};

template<typename T, typename N = node<T> >
N *reverse(node<T> *list)
{
	N *prev = nullptr;

	while(list)
	{
		N *next = list->next;
		list->next = prev;
		prev = list;
		list = next;
	}

	return prev;
}

template<typename S, typename T>
void show_node(S& s, node<T> *&list)
{
	s << list->data;
	list = list->next;
}

template<typename S, typename T>
S& operator<<(S& s, node<T> *list)
{
	if (list)
		show_node(s, list);

	while (list)
	{
		s << ", ";
		show_node(s, list);
	}
    
    return s;
}

template<typename T, typename N = node<T> >
N *make_list(size_t L)
{
	N *list = nullptr;

	for (size_t i=0; i<L; ++i)
		list = new N{T(i), list};

	return list;
}

template<typename T, typename N = node<T> >
void delete_list(node<T> *list)
{
	while (list)
	{
		N *next = list->next;
		delete list;
		list = next;
	}
}

int main()
{
	auto list = make_list<int>(10);
	std::cout << "As built: " << list << std::endl;

	list = reverse(list);
	std::cout << "Reversed: " << list << std::endl;

	delete_list(list);
}
