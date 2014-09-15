#include <type_traits>

// declare base class template for all managed classes
template <class Type>
class ManagedClass;

template <class Type>
class Manager
{
public:
	class CreateKey
	{
	private:
        // this key can only be created by Manager
		CreateKey() {};
		friend class Manager;
	};

	Type* createInstance()
	{
        // ManagedClass<Type> has to be a base of Type
        static_assert(std::is_base_of<ManagedClass<Type>, Type>::value, "Type has to be a ManagedClass");
        
        // create a object by using our key
		Type* ptr = new Type(CreateKey());
		return ptr;
	}
};

template <class Type>
class ManagedClass
{
public:
	typedef typename Manager<Type>::CreateKey CreateKey;
    
    // a ManagedClass can only be constructed with a key
	explicit ManagedClass(CreateKey) 
	{
	}
};

// every user defined class must derive from ManagedClass<T>
class MyManagedClass : public ManagedClass<MyManagedClass>
{
public:
    // it must take a key, otherwise we cannot construct our base
	explicit MyManagedClass(CreateKey key) : ManagedClass(key)
	{
	}
};

int main()
{
    // we cannot create a instance of MyManagedClass without the manager, because we cannot create a key for it
	Manager<MyManagedClass> manager;
	manager.createInstance();
}