#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <type_traits>
using namespace std;


class SpinLock
{
public:
    SpinLock(){cout << " ..Lock spin.. " ;}
    ~SpinLock(){cout << " ..unLock spin..\n ";}
};


class MutexLock
{
public:
    MutexLock(){cout << " ..Lock mutex.. " ;}
    ~MutexLock(){cout << " ..unLock mutex..\n ";}
};


template<class lk, typename T>
class GenProx
{
public:
    GenProx(T* t) : pt(t)
    {}
    
    T* operator->()
    {
        return pt;
    }
    
private:
    T* pt;
    lk sp;
};


template<typename T, typename lock>
class Mon2
{
public:
    Mon2(unique_ptr<T> _t): t(move(_t)){};
    GenProx<lock,T> operator->()
    {
        return GenProx<lock, T>(t.get());
    }
    T* release(){return t.release();}
private:
    unique_ptr<T> t;
};


template <class T>
using unique_ptr_def = unique_ptr<T, default_delete<T>>;

template <typename T>
class Store
{
    public:
    
    Store(T& _t) : t(_t){};
    T* operator->()
    {
        return &t;
    }
    operator T& ()
    {
        return t;
    }
    
    T& operator * ()
    {
        return t;
    }
private:
    
    T& t;
};


template <typename T>
class Own
{
    public:
    
    Own(const T& _t) : t(_t){};
     Own(T&& _t) : t(move(_t)){};
    T* operator->()
    {
        return &t;
    }
    operator T& ()
    {
        return t;
    }
    
    T& operator * ()
    {
        return t;
    }
private:
    
    T t;
};

template<typename T,  template <class> class storage = unique_ptr_def, class lock = MutexLock>
class Monitor
{
    public:
    Monitor(storage<T> _t): t(move(_t)){};
    
    template <class F>
    auto Action(F f) -> typename result_of<F(T&)>::type
    {
        lock lk;
        return f(*t);
    }
private:
    storage<T> t;
};

struct bthing
{

    virtual char doSomething()=0;
};

struct thing : public bthing
{
    
     thing()
    {
        cout << "thing created";
    }
    
    ~thing()
    {
        cout << "thing killed";
    }
    char doSomething(){cout << "Do Something "; return 'f';}
};

typedef Mon2<bthing, MutexLock> monitored_bThing;

struct tthing : public bthing
{
    char* data;
    tthing()
    {
        data = new char[47];
        cout << "tthing created, data allocated";
    }
    
     tthing(const tthing& other)
    {

        cout << "tthing copied";
    }
    
    tthing(tthing&& other)
    {
        data = other.data;
        other.data = nullptr;
        cout << "tthing moved";
    }
    ~tthing()
    {
        if(data)
        {
            cout << "data deleted ";
            delete [] data;
        }
        cout << "tthing killed";
    }
    
    char doSomething(){cout << "ttDo Something "; return 'b';}
};
















#include <set>
#include <functional>

// Class needed as we can't use <void> as a template argument
class void_arg
{};

// Forward declaration of Subscription
template <class T> class Subscription;

// Analagous to C# event. Create an instance of one, call Raise on it.
template <class T>
class Publisher 
{
    friend class Subscription<T>;
public:
	Publisher(){};

	~Publisher()
	{
		for(auto it = begin(subscriptions); it != end(subscriptions);it++)
		{
			auto subscription = (*it);
			subscription->EndSubscription();
		}
	}

	void operator()(const T& arg) const
	{
		for(auto it = begin(subscriptions); it != end(subscriptions);it++)
		{
			auto subscription = (*it);
			subscription->Notify(arg);
		}
	}

private:

	void Add(Subscription<T>* subscription)
	{
		ASSERT(subscription);
		if(subscriptions.find(subscription) == end(subscriptions))
			subscriptions.insert(subscription);
	}

	void Remove(Subscription<T>* subscription)
	{
		ASSERT(subscription);
		subscriptions.erase(subscription);
	}

	std::set<Subscription<T>*> subscriptions;

	// Cannot copy
	Publisher( Publisher& other );
	Publisher& operator=( const Publisher& rhs );
};

// Subscribe to a Publisher by creating one of these.
template <class T>
class Subscription 
{
	friend class Publisher<T>;
public:

	Subscription()
		: _publisher(nullptr)
	{
	}

	// Create by supplying a handler function and the publisher you are subscribing to
	Subscription(const std::function<void(const T&)>& notifyHandler, Publisher<T>& publisher)
		: _notifyHandler(notifyHandler),_publisher(&publisher)
	{
		ASSERT(_publisher);
		ASSERT(_notifyHandler);
		_publisher->Add(this);
	}

	// Move constructor
	Subscription( Subscription&& other ) :
		_publisher(other._publisher),
		_notifyHandler(std::move(other._notifyHandler))

	{
		if(_publisher)
		{
			_publisher->Remove(&other);
			_publisher->Add(this);
			other.EndSubscription();
		}
	}

	// Move assignment
	Subscription& operator=(Subscription&& other)
	{
		ASSERT(this != &other);
		_publisher = other._publisher;
		if(_publisher)
		{
			_publisher->Remove(&other);
			_publisher->Add(this);
		}
		_notifyHandler = std::move(other._notifyHandler);
		other.EndSubscription();
		return *this;
	}

	~Subscription()
	{
		if(_publisher)
			_publisher->Remove(this);
	}

private:

	void Notify(const T& arg) const
	{
		_notifyHandler(arg);
	}

	void EndSubscription()
	{
		_publisher=nullptr;
	}

	std::function<void(const T&	)> _notifyHandler;
	Publisher<T>* _publisher;

	// Cannot copy
	Subscription( const Subscription& other );
	Subscription& operator=( const Subscription& rhs );
};








int main()
{
      
    Monitor<tthing,Own> mon(tthing{});
    mon.Action([](bthing& t){return t.doSomething();});
        
  
}
