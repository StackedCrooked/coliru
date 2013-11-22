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
template <class... Args> class Subscription;


// Analagous to C# event. Create an instance of one, call Raise on it.
template <class... Args>
class Publisher
{
    friend class Subscription<Args...>;
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

	void operator()(Args... args) const
	{
		for(auto it = begin(subscriptions); it != end(subscriptions);it++)
		{
			auto subscription = (*it);
			subscription->Notify(args...);
		}
	}
	void Remove(Subscription<Args...>* subscription)
	{
	//	ASSERT(subscription);
		subscriptions.erase(subscription);
	}
private:

	void Add(Subscription<Args...>* subscription)
	{
	//	ASSERT(subscription);
		if(subscriptions.find(subscription) == end(subscriptions))
			subscriptions.insert(subscription);
	}



	std::set<Subscription<Args...>*> subscriptions;

	// Cannot copy
	Publisher( Publisher& other );
	Publisher& operator=( const Publisher& rhs );
};





// Subscribe to a Publisher by creating one of these.
template <class... Args>
class Subscription
{
	friend class Publisher<Args...>;
public:

	Subscription()
		: _publisher(nullptr)
	{
	}

	// Create by supplying a handler function and the publisher you are subscribing to
	Subscription(const std::function<void(Args...)>& notifyHandler, Publisher<Args...>& publisher)
		: _notifyHandler(notifyHandler),_publisher(&publisher)
	{
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
	//	ASSERT(this != &other);
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

	void Notify(Args... args) const
	{
		_notifyHandler(args...);
	}

	void EndSubscription()
	{
		_publisher=nullptr;
	}

	std::function<void(Args...)> _notifyHandler;
	Publisher<Args...>* _publisher;

	// Cannot copy
	Subscription( const Subscription& other );
	Subscription& operator=( const Subscription& rhs );
};



// Analagous to C# event. Create an instance of one, call Raise on it.
template <class... Args>
struct Event
{
    typedef shared_ptr<function<void(Args...)>> ptr;
    
    void operator ()(Args... args) const {
        for ( auto& handler : handlers)
            (*handler)(args...);
    }
    
    Event& operator+=(const ptr& handler) {
        handlers.insert(handler);
        return *this;
    }    

    Event& operator-=(const ptr& handler) {
        handlers.erase(handler);
        return *this;
    }
private:
	set<ptr> handlers;
};

template<class F>
 shared_ptr<function<F>> MakeFunctionPointer(F* f){
    return make_shared<function<F>>(f);
}


void foo(int a, int b){
    cout << "foo:" << a << ", " << b << "\n";
}



int main()
{
      
//    Monitor<tthing,Own> mon(tthing{});
//    mon.Action([](bthing& t){return t.doSomething();});
 
   Publisher<int, int> event;
   {
       Subscription<int, int> sub1([](int a, int b){cout << "a is " << a << " and  b is " << b << "\n";},event);
       Subscription<int, int> sub2([](int a, int b){cout << "2A IS " << a*2 << " AND 2B IS " << 2*b << "\n";},event);
       event(4,5);
       event.Remove(&sub1);
       event(1,3);
   }
   
Event<int, int> ev;
ev += MakeFunctionPointer(foo);   // 1
//([](int a, int b) -> void {cout << "Lambda:" << a << ", " << b << "\n";}));
auto fp = MakeFunctionPointer(&foo);

{
     auto spf =  shared_ptr< function<void(int, int)> > ( new function<void(int, int)>(foo));
     ev += spf;
     (*spf)(2,4);
       ev -= spf;
}
 // auto spf =  make_shared(pf);
//ev += fp;
//delete fp;

ev(4,5);    //2 


//ev += new function<void(int,int)>([](int a, int b){cout << "Lambda:" << a << ", " << b << "\n";});
ev(1,2);
//ev -= MakeFunctionPointer(foo);
ev(3,4);
   

  
}
