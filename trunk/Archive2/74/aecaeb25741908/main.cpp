#include <functional>
#include <type_traits>
#include <utility>

template <std::size_t... Is>
struct indices {};

template <std::size_t N, std::size_t... Is>
struct build_indices
  : build_indices<N-1, N-1, Is...> {};

template <std::size_t... Is>
struct build_indices<0, Is...> : indices<Is...> {};

template<int I> struct placeholder{};

namespace std{
template<int I>
struct is_placeholder< ::placeholder<I>> : std::integral_constant<int, I>{};
} // std::

namespace detail{
template<std::size_t... Is, class F, class... Args>
auto easy_bind(indices<Is...>, F const& f, Args&&... args)
  -> decltype(std::bind(f, std::forward<Args>(args)..., placeholder<1 + Is>{}...))
{
    return std::bind(f, std::forward<Args>(args)..., placeholder<1 + Is>{}...);
}
} // detail::

template<class F, class... FArgs, class... Args>
auto easy_bind(F const& f, Args&&... args)
    -> decltype(detail::easy_bind(build_indices<sizeof...(FArgs) - sizeof...(Args)>{}, f, std::forward<Args>(args)...))
{
    return detail::easy_bind(build_indices<sizeof...(FArgs) - sizeof...(Args)>{}, f, std::forward<Args>(args)...);
}

using namespace std;

template<typename... Params>
class Event
{
    /*
    *    Structures
    */
    struct Node
    {
        function<void(Params...)> dat;
		Node* next;
		Node* prev;
        
        void replace(function<void(Params...)> func)
        {
            dat = func;
        } //replace
	}; //Node

	/*
	*	Fields
	*/
	Node* first;
	Node* last;

	bool reversed;
	int length;

public:
	/*
	*	Types
	*/
	typedef Node* id;

	/*
	*	Constructors
	*/
	Event()
	{
		length = 0;
	
		first = NULL;
		last = NULL;
	
		reversed = false;
	} //Event
	
	~Event()
	{
		clear();
	} //~Event

	/*
	*	Data Manipulation Operations
	*/
	template<class T, class... Args>
	id reg(T&& func, Args&&... args)
	{
		++length;
	
		Node* node = new Node();
		node->dat = easy_bind<T, Params..., Args...>(func, args...);
        
		if (reversed)
		{
			node->prev = NULL;
			node->next = first;
		
			if (first == NULL)
			{
				last = node;
			} //if
			else
			{
				first->prev = node;
			} //else
		
			first = node;
		} //if
		else
		{
			node->next = NULL;
			node->prev = last;
		
			if (last == NULL)
			{
				first = node;
			} //if
			else
			{
				last->next = node;
			} //else
		
			last = node;
		} //else
	
		return node;
	} //reg
    
    template<class... Args>
    id regEvent(Event<Params..., Args...>& event, Args&&... args)
    {
        easy_bind([](Event<Params..., Args...>& event, Args&&... args, Params&&... params) { event.exec(forward<Params>(params)..., forward<Args>(args)...); }, event, args...);
        return NULL;
        //return reg(easy_bind([](Event<Params..., Args...>& event, Args&&... args, Params&&... params) { event.exec(forward<Params>(params)..., forward<Args>(args)...); }, event, args...));
    } //regEvent
	
	void unreg(id eventId)
	{
		--length;
	
		if (eventId->next)
		{
			eventId->next->prev = eventId->prev;
		} //if
		else
		{
			last = eventId->prev;
		} //else
		if (eventId->prev)
		{
			eventId->prev->next = eventId->next;
		}
		else
		{
			first = eventId->next;
		} //else
	
		delete eventId;
	} //unreg
	
	void clear()
	{
		Node* next;
	
		while (first)
		{
			next = first->next;
			delete first;
			first = next;
		} //while
	
		last = NULL;
	} //clear
	
	/*
	*	Structure Manipulation Operations
	*
	*/
	void reverse()
	{
		if (first)
		{
			Node* node = first;
			Node* next = node->next;
	
			while (next)
			{
				node->next = node->prev;
				node->prev = next;
				node = next;
				next = node->next;
			} //while
	
			last->next = last->prev;
			last->prev = next;
	
			node = last;
			last = first;
			first = node;
	
			reversed = !reversed;
		} //if
	} //reverse

	/*
	*	Execution Operations
	*/
	void exec(Params&&... args)
	{
		if (first)
		{
			function<void(Params...)>* actions[length];
			int i = 0;
	
			Node* node = first;
	
			while (node)
			{
			    actions[i++] = &node->dat;
				node = node->next;
			} //while
		
			int length = this->length;
		
			for (i = 0; i < length; ++i)
			{
				(*actions[i])(args...);
			} //for
		} //if
	} //exec
}; //Event

#include <iostream>
#include <string>

class O
{
    public:
    void f1(string bound, int i, int i2)
    {
        cout << bound << ", " << i << ", " << i2 << endl;
    } //f1
    
    O(int i)
    {
        cout << "constructor " << i << endl;
        
        delete this;
    }
};

void f1(string bound, int i, int i2)
{
    cout << bound << ", " << i << ", " << i2 << endl;
} //f1
    
int main(int argc, char** argv)
{
    //O o;
    
    Event<int, int> e1;
    Event<int, int, int> e2;
    
    e2.reg([](int i, int i2, int i3) { cout << i3 << ", " << i << ", " << i2 << endl; });
    
    //e1.regEvent(e2, 6);
	
	Event<int, int>::id eventId2 = e1.reg([](string bound, int i, int i2) { cout << bound << ", " << i << ", " << i2 << endl; }, "hello lambda");
    Event<int, int>::id eventId3 = e1.reg(f1, "hello function");
    
	e1.exec(1, 2);
	
	return 0;
} //main