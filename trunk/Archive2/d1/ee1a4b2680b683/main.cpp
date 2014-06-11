#include <iostream>
#include <stack>
#include <thread>
#include <condition_variable>
#include <functional> /* Pour l'exemple */

template <typename T>
class mystack // si on hérite on risque d'avoir des problèmes avec les delete et delete[@
// voir [ http://stackoverflow.com/questions/2034916/is-it-okay-to-inherit-implementation-from-stl-containers-rather-than-delegate ]
{
private:
    std::stack<T> internal; // Les containers de la STL sont thread-safe [ http://en.cppreference.com/w/cpp/container ]
public:
    std::condition_variable not_empty;
    std::condition_variable is_empty;
	std::mutex mtx;
public:
    mystack(): internal(){}
    ~mystack()=default;
    mystack(mystack const& stk): internal(stk.internal){}
    mystack(mystack&& stk): internal(std::move(stk.internal)){}
    // definir les autres allocations possibles pour être 100% compatible avec std::stack
    // implementer size() et swap()
    typename std::stack<T>::reference& top()
    {
        return internal.top();
    }
    typename std::stack<T>::const_reference& top() const
    {
        return internal.top();
    }
    bool empty() const
    {
        return internal.empty();
    }
	void push(const typename std::stack<T>::value_type& val)
	{
		bool empty_= empty();
		internal.push(val);
		if(empty_)
			not_empty.notify_all();
	}
	void push(typename std::stack<T>::value_type&& val)
	{
		bool empty_= empty();
		internal.push(std::forward<typename std::stack<T>::value_type>(val));
		if(empty_)
			not_empty.notify_all();
	}
	template <class... Args>
	void emplace(Args&&... args)
	{
		bool empty_= empty();
		internal.emplace(std::forward<Args>(args)...);
		if(empty_)
			not_empty.notify_all();
	}
	void pop()
	{
		internal.pop();
		if( empty())
			is_empty.notify_all();

	}
};

void fun1(mystack<std::function<bool()>>& stk, int const& n)
{
	if(n<0)
		return;
	for(int itr=0;itr<n;++itr)
	{
		std::unique_lock<std::mutex> lck(stk.mtx);
		stk.is_empty.wait(lck, [&](){ return stk.empty(); });
		// stk est désormais vide
		std::cout<< "fun1: "<< itr<<std::endl;
        stk.push(std::function<bool()>([itr,n](){return itr==n-1;}));
	}
}

void fun2(mystack<std::function<bool()>>& stk)
{
	bool done=false;
	while( !done)
	{
        mystack<std::function<bool()>> stk2(stk);
		std::unique_lock<std::mutex> lck(stk.mtx);
		stk.not_empty.wait(lck, [&](){ return !stk.empty(); });
		// On prend le premier élement
		auto msg=stk.top();
		stk.pop();
		// Tu fais ton traitement avec 'msg' et tu mets à jour 'done'
		std::cout<< "fun2"<<std::endl;
        done=msg(); // par exemple
	}
}

int main()
{
	mystack<std::function<bool()>> stk; // une version sans pointeurs serait meilleure/plus simple
    int n=7;
	std::thread thread1(fun1,std::ref(stk),std::ref(n));
	std::thread thread2(fun2, std::ref(stk));
	thread1.join();
	thread2.join();
    std::cout<< "Fin."<<std::endl;
	return 0;
}
